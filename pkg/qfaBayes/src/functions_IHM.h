#ifndef _functions_h
#define _functions_h

/* public common function prototypes */
double gauss_sample_IHM(struct_data_IHM *D ,int start, int N,
  double x[],double tau,double mu_0,double tau_0);

double MCMC_base_IHM(struct_data_IHM *D,struct_para_IHM *D_para,
  struct_priors_IHM *D_priors,double *accept,double *h,double para,
  double (*foo)(struct struct_data_IHM *D,struct struct_para_IHM *D_para,
  struct struct_priors_IHM *D_priors,double,int,int,int),int c,int l, int m);
  
double MCMC_alpha_c_IHM(struct_data_IHM *D,struct_para_IHM *D_para,
  struct_priors_IHM *D_priors,double para,int c,int l, int m);

int gibbsandMHloop_IHM(int iter,int thin,struct_data_IHM *D,
  struct_para_IHM *D_para,struct_priors_IHM *D_priors,
  struct_tuning_IHM *D_tuning,struct_adaptive_IHM *D_adaptive,
  int print,int adaptive_phase,double *OUT,char **HEADER);
  
int adaptive_phase_process_IHM(struct_tuning_IHM *tuning,
  struct_adaptive_IHM *adaptive,int print,int iter);
#endif
