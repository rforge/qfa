#include <stdio.h>
#include <math.h>
#include <stdlib.h>    
#include <unistd.h>
#include <time.h>
#include <R.h>
#include <Rmath.h>

typedef struct struct_data_JHM {
  double *y, *x;
  int L, M,N,*NoORF,*NoSUM,*NoTIME,SHIFTlmn,SHIFTmn, maxy,maxTIMEa,maxTIMEb;
} struct_data_JHM;

typedef struct struct_para_JHM {
  double
    *alpha_c,
    *beta_c,
    *delta_l,
    *gamma_cl,	        sigma_gamma,
    *omega_cl,            sigma_omega,
     
    *K_clm,            *tau_K_cl,
    *r_clm,            *tau_r_cl,

    *K_o_l,            sigma_K_o,
    *r_o_l,            sigma_r_o,
    *nu_l,             sigma_nu,

    K_p,
    r_p,
    nu_p,
    P,
    *tau_K_p_c,*tau_r_p_c,*sigma_tau_K_c,*sigma_tau_r_c;
} struct_para_JHM;

typedef struct struct_priors_JHM {
  double
    alpha_mu,               eta_alpha,
    beta_mu,                eta_beta,
    p,    
    eta_gamma,              psi_gamma,
    eta_omega,              psi_omega,  

    sigma_K,                phi_K,
    sigma_r,                phi_r,

    eta_K_o,                psi_K_o,
    eta_r_o,                psi_r_o,
    eta_nu,                 psi_nu,

    K_mu,                   eta_K_p,
    r_mu,                   eta_r_p,
    nu_mu,                  eta_nu_p,
    P_mu,                   eta_P,
    df,df2,

    tau_K_mu,tau_r_mu,
    eta_tau_K,eta_tau_r,
    psi_tau_r_p,psi_tau_K_p,
    eta_tau_K_p,eta_tau_r_p,
    psi_tau_K,psi_tau_r;
} struct_priors_JHM;

typedef struct struct_tuning_JHM {
  double 
   alpha_c,
    beta_c,
    gamma_cl,	        sigma_gamma,
    omega_cl,           sigma_omega,
     
    K_clm,            tau_K_cl,
    r_clm,            tau_r_cl,

    K_o_l,            sigma_K_o,
    r_o_l,            sigma_r_o,
    nu_l,             sigma_nu,

    K_p,
    r_p,
    P,
    tau_K_p_c,tau_r_p_c,sigma_tau_K_c,sigma_tau_r_c;
} struct_tuning_JHM;

typedef struct struct_adaptive_JHM {
  double 
   alpha_c,
    beta_c,
    gamma_cl,	        sigma_gamma,
    omega_cl,           sigma_omega,
     
    K_clm,            tau_K_cl,
    r_clm,            tau_r_cl,

    K_o_l,            sigma_K_o,
    r_o_l,            sigma_r_o,
    nu_l,             sigma_nu,

    K_p,
    r_p,
    P,
    tau_K_p_c,tau_r_p_c,sigma_tau_K_c,sigma_tau_r_c;
} struct_adaptive_JHM;