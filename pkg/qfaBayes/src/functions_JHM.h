#ifndef _functions_h
#define _functions_h

/* public common function prototypes */
double logistic_function_JHM(double t,double K, double r, double P);
double logistic_function_E_JHM(double t,double K, double r, double P);

double gauss_sample_JHM(struct_data_JHM *D ,int start, int N,double x[],double tau,double mu_0,double tau_0);

double MCMC_base_JHM(struct_data_JHM *D,struct_para_JHM *D_para,
  struct_priors_JHM *D_priors,double *a,double *h,double para,
  double (*foo)(struct struct_data_JHM *D,struct struct_para_JHM *D_para,
  struct struct_priors_JHM *D_priors,double,int,int,int),int c,int l, int m);

double MCMC_P_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_nu_l_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_K_clm_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_r_clm_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_K_o_l_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_r_o_l_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_alpha_c_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_beta_c_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double aug_delta_l_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,int l);
double MCMC_gamma_cl_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_omega_cl_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_sigma_gamma_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_sigma_omega_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_sigma_K_o_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_sigma_r_o_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_tau_K_cl_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);
double MCMC_tau_r_cl_JHM(struct_data_JHM *D,struct_para_JHM *D_para,struct_priors_JHM *D_priors,double para,int c,int l, int m);

int gibbsandMHloop_JHM(int iter,int thin,struct_data_JHM *D,
  struct_para_JHM *D_para,struct_priors_JHM *D_priors,
  struct_tuning_JHM *D_tuning,struct_adaptive_JHM *D_adaptive,
  int print,int adaptive_phase,double *OUT,char **HEADER);

int adaptive_phase_process_JHM(struct_tuning_JHM *tuning,
  struct_adaptive_JHM *adaptive,int print,int iter);
  
#endif
