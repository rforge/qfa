#include "headers_IHM.h"
#include "datain_IHM.h"


int datadouble_IHM(struct_data_IHM *D,double *QFADyA,double *QFADyB)
{
	int i;
	for (i=0;i<D->SHIFTmn;i++){
		D->y[i]=QFADyA[i];
	}

	for (i=D->SHIFTmn;i<D->MAXmn;i++){
		D->y[i]=QFADyB[i];
	}
return 0;
}

/*INZ*/

int inzstruct_priors_IHM(struct_priors_IHM *D_priors,double *PRIORS)
{
    D_priors->Z_mu=PRIORS[0];	

	D_priors->eta_Z_p=PRIORS[1];      

	D_priors->eta_Z=PRIORS[2];	

	D_priors->psi_Z=PRIORS[3];

	D_priors->eta_nu=PRIORS[4];	

	D_priors->psi_nu=PRIORS[5];  

	D_priors->nu_mu=PRIORS[6];    	

	D_priors->eta_nu_p=PRIORS[7]; 

	D_priors->alpha_mu=PRIORS[8];      	

	D_priors->eta_alpha=PRIORS[9];

	D_priors->p=PRIORS[10];    

	D_priors->eta_gamma=PRIORS[11];	

	D_priors->psi_gamma=PRIORS[12];
		
	D_priors->df=3;
return 0;
}


int inzstruct_data_IHM(struct_data_IHM *data,int *QFAIA,double *QFADyA,int *QFADNoORFA,int *QFAIB,double *QFADyB,int *QFADNoORFB)
{
	int i;
	long size;
		data->L=QFAIA[0];     
		data->L=QFAIB[0];
	size=2*data->L;
	data->NoORF=malloc(size*sizeof(double));    

 for (i=0;i<(data->L);i++){
data->NoORF[i]=QFADNoORFA[i];
data->NoORF[i+data->L]=QFADNoORFB[i];
}


	data->NoSUM=malloc(size*sizeof(double));  
	filldata_IHM(data);

	size=data->MAXmn;
	data->y=malloc(size*sizeof(double));  

	datadouble_IHM(data,QFADyA,QFADyB);
return 0;
}



int inzstruct_para_IHM(struct_para_IHM *para,struct_data_IHM *data,struct_priors_IHM *priors)
{
	long size;
	size=data->L;
	para->delta_l=malloc(size*sizeof(double));
	para->gamma_cl=malloc(size*sizeof(double));
	para->Z_l=malloc(size*sizeof(double));
	size=data->L*2;/***/
	para->nu_cl=malloc(size*sizeof(double));
	size=2;
	para->alpha_c=malloc(size*sizeof(double));
	fillpara_IHM(para,data,priors);
return 0;
}

/*FILL*/

int inzstruct_tuning_IHM(struct_tuning_IHM *tuning,double *TUNING)
{
    tuning->Z_l=TUNING[0],          	  tuning->sigma_Z=TUNING[1], 
    tuning->nu_cl=TUNING[2],            tuning->sigma_nu=TUNING[3],
    tuning->gamma_cl=TUNING[4],	      tuning->sigma_gamma=TUNING[5],
	tuning->alpha_c=TUNING[6],
	tuning->Z_p=TUNING[7];

return 0;
}

int inzstruct_adaptive_IHM(struct_adaptive_IHM *adaptive)
{
    adaptive->Z_l=0,          	  adaptive->sigma_Z=0, 
    adaptive->nu_cl=0,            adaptive->sigma_nu=0,
    adaptive->gamma_cl=0,	      adaptive->sigma_gamma=0,
	adaptive->alpha_c=0,
	adaptive->Z_p=0;
 
return 0;
}

int filldata_IHM(struct_data_IHM *D)
{
	int l;
	D->NoSUM[0]=0;
	for (l=1;l<(D->L);l++){
		D->NoSUM[l]=D->NoSUM[l-1]+D->NoORF[l-1];
	}

	D->NoSUM[D->L]=D->SHIFTmn=D->NoSUM[D->L-1]+D->NoORF[D->L-1];

	for (l=(1+D->L);l<(2*D->L);l++){
		D->NoSUM[l]=D->NoSUM[l-1]+D->NoORF[l-1];
	}
	
	D->MAXmn=D->NoSUM[2*D->L-1]+D->NoORF[2*D->L-1];

return 0;
}

int fillpara_IHM(struct_para_IHM *D_para, struct_data_IHM *D,struct_priors_IHM *D_priors)
{
  int l,m,mm,ll;
  double SUM=0,SUMa=0,SUMb=0;
	/*initials*/
	for (l=0;l<D->L;l++){
	  for (m=0;m<D->NoORF[l];m++){
	    mm=D->NoSUM[l]+m;
	    SUM += D->y[mm];
	  }
	  if ((SUM/D->NoORF[l])<1){
	    D_para->Z_l[l]=0;
	  }
	   else{
	    D_para->Z_l[l]=log(SUM/D->NoORF[l]);/***/
	     }
	    SUMa+=SUM/D->NoORF[l];
	  SUM=0;
	}

	D_para->Z_p=log(SUMa/D->L);

	D_para->sigma_Z=D_priors->eta_Z;     


	for (l=0;l<2*D->L;l++)          {D_para->nu_cl[l]=D_priors->nu_mu;}          
	D_para->sigma_nu=D_priors->eta_nu;   
  
	D_para->nu_p=D_priors->nu_mu;    

	for (l=0;l<D->L;l++)          {D_para->gamma_cl[l]=0;} 

	for (l=0;l<D->L;l++)          {D_para->delta_l[l]=1;}/*!*/  

	D_para->alpha_c[0]=0;/**/
	
	SUMa=SUMb=0;
	for (l=0;l<D->L;l++){
	  SUMa+=exp(D_para->Z_l[l]);
	  ll=l+D->L;
	  for (m=0;m<D->NoORF[ll];m++){
	    mm=D->NoSUM[ll]+m;
	      SUM+=D->y[mm];
	  }
	  if ((SUM/D->NoORF[ll])<1){
	    SUMb+=0;
	  }
	  else{
	    SUMb+=(SUM/D->NoORF[ll]);
	  }
	  SUM=0;
	}
	D_para->alpha_c[1]=log(SUMb/SUMa);
	D_para->sigma_gamma=D_priors->eta_gamma;
	
return 0;
}

/* eof  */
