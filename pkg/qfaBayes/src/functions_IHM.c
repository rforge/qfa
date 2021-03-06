#include "headers_IHM.h"
#include "functions_IHM.h"
#include "print_IHM.h"

/*trun*/
double trun_const_low_IHM(double x,double m, double l)
{
  return(1-0.5-(  (pow(3*l,0.5))*(x-m)/(((l*pow(x-m,2))+3))  +atan((pow(l/3,0.5))*(x-m)))/M_PI);
}

/*Gibbs*/

double gauss_sample_IHM(struct_data_IHM *D ,int start, int N,double x[],double tau,double mu_0,double tau_0){
  double vec,Ndouble,SUM=0;
  int i;
  Ndouble=N;
  for (i=start;i<(start+N);i++){SUM=SUM+x[i];}
  vec=rnorm((tau_0*mu_0+tau*SUM)/(tau_0+Ndouble*tau),1/sqrt(tau_0+Ndouble*tau));
  return(vec);
}

/*MCMC MH*/
double MCMC_base_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double *accept,double *h,double para,double (*foo)(struct struct_data_IHM *D,struct struct_para_IHM *D_para,struct struct_priors_IHM *D_priors,double,int,int,int),int c,int l, int m){
  double logu,logaprob,can;
   can=rnorm(para,*h); /*can=para+gsl_ran_gaussian(RNG,*h);*/
  logaprob=(*foo)(D,D_para,D_priors,can,c,l,m)-(*foo)(D,D_para,D_priors,para,c,l,m);

    logu=log(1-runif(0,1));/*logu=log(1-gsl_rng_uniform(RNG));*/
  if (logaprob>logu){para=can;*accept=*accept+1;}
  return(para); 
}

double MCMC_base_truncate_low_IHM(double truncate, struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double *accept,double *h,double para,double (*foo)(struct struct_data_IHM *D,struct struct_para_IHM *D_para,struct struct_priors_IHM *D_priors,double,int,int,int),int c,int l, int m){
  double logu,logaprob,can;
    can=rnorm(para,*h);
    if(can<(truncate)){
      can=para;
    }
 
  logaprob=(*foo)(D,D_para,D_priors,can,c,l,m)-(*foo)(D,D_para,D_priors,para,c,l,m);

  logu=log(1-runif(0,1));
  if (logaprob>logu){para=can;*accept=*accept+1;}
  return(para);
}

double MCMC_nu_cl_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,F,SUM=0;
  int ll,mm;
    ll=c*D->L+l;
    for (m=0;m<D->NoORF[ll];m++){
      mm=D->NoSUM[ll]+m;
      F=D->y[mm]-exp(D_para->alpha_c[c]+D_para->Z_l[l]+c*D_para->delta_l[l]*D_para->gamma_cl[l]);
      SUM+=-para+F*F*exp(para);
    }
  F=para-D_para->nu_p;
  density=F*F*exp(D_para->sigma_nu)+SUM; 
  return(-0.5*density); 
}

double MCMC_sigma_nu_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,SUM=0,F;
  for (l=0;l<2*D->L;l++){
    F=D_para->nu_cl[l]-D_para->nu_p;
    SUM=-para+F*F*exp(para)+SUM;
  }
  F=para-D_priors->eta_nu;
  density=F*F*D_priors->psi_nu+SUM; 
  return(-0.5*density); 
}

double MCMC_alpha_c_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,F,SUM=0;
  int ll,mm;
  for (l=0;l<D->L;l++){
    ll=D->L+l;
    for (m=0;m<D->NoORF[ll];m++){
      mm=D->NoSUM[ll]+m;
      F=D->y[mm]-exp( para+D_para->Z_l[l]+D_para->delta_l[l]*D_para->gamma_cl[l]);
      SUM+=F*F*exp(D_para->nu_cl[ll]);
    }
  }
  F=para-D_priors->alpha_mu;
  density=F*F*D_priors->eta_alpha+SUM; 

  return(-0.5*density); 
}

/*Data Aug*/
double aug_delta_l_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,int l){
  double u,para,PRODa=0,PRODb=0,F;
  int m,ll=D->L+l,mm;
  for (m=0;m<D->NoORF[ll];m++){
    mm=D->NoSUM[ll]+m;
    F=D->y[mm]-exp(D_para->alpha_c[1]+D_para->Z_l[l]);
    PRODa+=-0.5*F*F*exp(D_para->nu_cl[ll]);
  }
  PRODa+=log(1-D_priors->p);

  for (m=0;m<D->NoORF[ll];m++){
    mm=D->NoSUM[ll]+m;
    F=D->y[mm]-exp(D_para->alpha_c[1]+D_para->Z_l[l]+D_para->gamma_cl[l]);
    PRODb+=-0.5*F*F*exp(D_para->nu_cl[ll]);
  }
  PRODb+=log(D_priors->p);

  u=runif(0,1); /* u=gsl_rng_uniform(RNG); */
  if (log(u/(1-u))<(PRODa-PRODb) ){para=0;}
  else{para=1;}
  return(para);
}

double MCMC_Z_p_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,F,SUM=0;
  for (l=0;l<D->L;l++){
    F=exp(D_para->Z_l[l])-exp(para);
    SUM+=(1+D_priors->df)*log(1+pow(F,2)*exp(D_para->sigma_Z)/D_priors->df)/**/+2*log(trun_const_low_IHM(0,exp(para),exp(D_para->sigma_Z)));
  }
  F=para-D_priors->Z_mu;
  density=F*F*D_priors->eta_Z_p+SUM; 
  return(-0.5*density); 
}

double MCMC_Z_l_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,F,SUM=0;
  int ll,mm;
  for (c=0;c<2;c++){
    ll=c*D->L+l;
    for (m=0;m<D->NoORF[ll];m++){
      mm=D->NoSUM[ll]+m;
      F=D->y[mm]-para*exp(D_para->alpha_c[c]+c*D_para->delta_l[l]*D_para->gamma_cl[l]);
      SUM+=F*F*exp(D_para->nu_cl[ll]);
    }
  }
  F=para-exp(D_para->Z_p);
  density=(1+D_priors->df)*log(1+pow(F,2)*exp(D_para->sigma_Z)/D_priors->df)+SUM;
  return(-0.5*density); 
}

double MCMC_sigma_Z_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,SUM=0,F;
  for (l=0;l<D->L;l++){
    F=exp(D_para->Z_l[l])-exp(D_para->Z_p);
    SUM+=(1+D_priors->df)*log(1+pow(F,2)*exp(para)/D_priors->df)-(para)/**/+2*log(trun_const_low_IHM(0,exp(D_para->Z_p),exp(para)));
  }
  F=para-D_priors->eta_Z;
  density=F*F*D_priors->psi_Z+SUM; 
  return(-0.5*density); 
}

double MCMC_gamma_cl_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,F,SUM=0;
  int ll=D->L+l,mm;
  for (m=0;m<D->NoORF[ll];m++){
    mm=D->NoSUM[ll]+m;
    F=D->y[mm]-exp( D_para->alpha_c[1]+D_para->Z_l[l]+D_para->delta_l[l]*log(para));
    SUM+=F*F*exp(D_para->nu_cl[ll]);
  }
  F=para-1;
  density=(1+D_priors->df)*log(1+pow(F,2)*exp(D_para->sigma_gamma)/D_priors->df)+SUM; 
  return(-0.5*density); 
}

double MCMC_sigma_gamma_IHM(struct_data_IHM *D,struct_para_IHM *D_para,struct_priors_IHM *D_priors,double para,int c,int l, int m){
  double density,F,SUM=0;
  for (l=0;l<D->L;l++){
    F=exp(D_para->gamma_cl[l])-1;
    SUM+=(1+D_priors->df)*log(1+pow(F,2)*exp(para)/D_priors->df)-(para)/**/+2*log(trun_const_low_IHM(0,1,exp(para)));
  }
  F=para-D_priors->eta_gamma;
  density=F*F*D_priors->psi_gamma+SUM; 
  return(-0.5*density); 
}

/*Gibbs and MH steps*/
int gibbsandMHloop_IHM(int iter,int thin,struct_data_IHM *D,
  struct_para_IHM *D_para,struct_priors_IHM *D_priors,
  struct_tuning_IHM *D_tuning,struct_adaptive_IHM *D_adaptive,int print,
  int adaptive_phase,double *OUT,char **HEADER){
int i,j,l,*T,t,c,ll;
T=&t;
*T=0;

if (print==0){
	printheader_IHM(D,HEADER);
}

for (i=0;i<iter;i++){
	for (j=0;j<thin;j++){
		D_para->alpha_c[1]=MCMC_base_IHM(D,D_para,D_priors,&D_adaptive->alpha_c,&D_tuning->alpha_c,D_para->alpha_c[1],MCMC_alpha_c_IHM,-999,-999,-999);
		D_para->sigma_gamma=MCMC_base_IHM(D,D_para,D_priors,&D_adaptive->sigma_gamma,&D_tuning->sigma_gamma,D_para->sigma_gamma,MCMC_sigma_gamma_IHM,-999,-999,-999);      
		D_para->sigma_nu=MCMC_base_IHM(D,D_para,D_priors,&D_adaptive->sigma_nu,&D_tuning->sigma_nu,D_para->sigma_nu,MCMC_sigma_nu_IHM,-999,-999,-999);
		D_para->Z_p=MCMC_base_IHM(D,D_para,D_priors,&D_adaptive->Z_p,&D_tuning->Z_p,D_para->Z_p,MCMC_Z_p_IHM,-999,-999,-999);
		D_para->sigma_Z=MCMC_base_IHM(D,D_para,D_priors,&D_adaptive->sigma_Z,&D_tuning->sigma_Z,D_para->sigma_Z,MCMC_sigma_Z_IHM,-999,-999,-999);   
		D_para->nu_p=gauss_sample_IHM(D,0,2*D->L,D_para->nu_cl,exp(D_para->sigma_nu),D_priors->nu_mu,D_priors->eta_nu_p);

		for (l=0;l<D->L;l++){
			D_para->delta_l[l]=aug_delta_l_IHM(D,D_para,D_priors,l);
			D_para->gamma_cl[l]=MCMC_base_truncate_low_IHM(0,D,D_para,D_priors,&D_adaptive->gamma_cl,&D_tuning->gamma_cl,exp(D_para->gamma_cl[l]),MCMC_gamma_cl_IHM,-999,l,-999);
			D_para->gamma_cl[l]=log( D_para->gamma_cl[l]);
			D_para->Z_l[l]=MCMC_base_truncate_low_IHM(0,D,D_para,D_priors,&D_adaptive->Z_l,&D_tuning->Z_l,exp(D_para->Z_l[l]),MCMC_Z_l_IHM,-999,l,-999);
			D_para->Z_l[l]=log( D_para->Z_l[l]);
			
			for (c=0;c<2;c++){
				ll=c*D->L+l;
				D_para->nu_cl[ll]=MCMC_base_IHM(D,D_para,D_priors,&D_adaptive->nu_cl,&D_tuning->nu_cl,D_para->nu_cl[ll],MCMC_nu_cl_IHM,c,l,-999);
				
			}
		}
	  
		if (print==0){
			if (adaptive_phase>0){
				if (adaptive_phase>i){
					adaptive_phase_process_IHM(D_tuning,D_adaptive,print,iter);	
				}
			}
		}	
    }
	if (print==1){
		printdata_IHM(D,D_para,OUT,T);
	}
}
  return 0;
}

int adaptive_phase_process_IHM(struct_tuning_IHM *tuning,
  struct_adaptive_IHM *adaptive,int print,int iter){
  double explore=1.01,exploredown=1/1.01;

	/*	if (adaptive->Z_l==1){
			tuning->Z_l=tuning->Z_l*explore;
		} else {
			tuning->Z_l=tuning->Z_l*exploredown;
		}*/
		
		if (adaptive->sigma_Z==1){
			tuning->sigma_Z=tuning->sigma_Z*explore;
		} else {
			tuning->sigma_Z=tuning->sigma_Z*exploredown;
		}
		
	/*	if (adaptive->nu_cl==1){
			tuning->nu_cl=tuning->nu_cl*explore;
		} else {
			tuning->nu_cl=tuning->nu_cl*exploredown;
		}*/
		
		if (adaptive->sigma_nu==1){
			tuning->sigma_nu=tuning->sigma_nu*explore;
		} else {
			tuning->sigma_nu=tuning->sigma_nu*exploredown;
		}

		if (adaptive->alpha_c==1){
			tuning->alpha_c=tuning->alpha_c*explore;
		} else {
			tuning->alpha_c=tuning->alpha_c*exploredown;
		}
		
		/*if (adaptive->gamma_cl==1){
			tuning->gamma_cl=tuning->gamma_cl*explore;
		} else {
			tuning->gamma_cl=tuning->gamma_cl*exploredown;
		}*/

		if (adaptive->sigma_gamma==1){
			tuning->sigma_gamma=tuning->sigma_gamma*explore;
		} else {
			tuning->sigma_gamma=tuning->sigma_gamma*exploredown;
		}
		
		if (adaptive->Z_p==1){
			tuning->Z_p=tuning->Z_p*explore;
		} else {
			tuning->Z_p=tuning->Z_p*exploredown;
		}		
 
    adaptive->Z_l=0,          	  adaptive->sigma_Z=0, 
    adaptive->nu_cl=0,            adaptive->sigma_nu=0,
	adaptive->alpha_c=0,
    adaptive->gamma_cl=0,	      adaptive->sigma_gamma=0,
	adaptive->Z_p=0;
  
return 0;
}
