\name{IHM_main}
\alias{IHM_main}
\title{Runs IHM C code}
\description{
For use with control and query SHM output.
Runs IHM C code
}
\usage{
IHM_main(burn,iters,thin,adaptive_phase,QFA.IA,QFA.yA,
  QFA.NoORFA,QFA.IB,QFA.yB,QFA.NoORFB,PRIORS,TUNING)
}
\arguments{
  \item{burn}{Burn-in period}
  \item{iters}{Number of iterations in final sample}
  \item{thin}{Amount of thinning}
  \item{adaptive_phase}{Total length of adaptive phase within burn in period}
  \item{QFA.IA}{QFA.IA}
  \item{QFA.yA}{QFA.yA}
  \item{QFA.NoORFA}{QFA.NoORFA}
  \item{QFA.IB}{QFA.IB}
  \item{QFA.yB}{QFA.yB}
  \item{QFA.NoORFB}{QFA.NoORFB}
  \item{PRIORS}{PRIORS}
    \item{TUNING}{TUNING}
}
\value{
IHM output
}
\keyword{qfaBayes}
