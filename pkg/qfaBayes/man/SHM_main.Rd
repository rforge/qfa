\name{SHM_main}
\alias{SHM_main}
\title{Runs SHM C code}
\description{
For use with SHM post processed Colonyzer output.
Runs SHM C code
}
\usage{
SHM_main(burn,iters,thin,adaptive_phase,QFA.I,QFA.y,QFA.x,
  QFA.NoORF,QFA.NoTIME,PRIORS,TUNING)
}
\arguments{
  \item{burn}{Burn-in period}
  \item{iters}{Number of iterations in final sample}
  \item{thin}{Amount of thinning}
  \item{adaptive_phase}{Total length of adaptive phase within burn in period}
  \item{QFA.I}{QFA.I}
  \item{QFA.y}{QFA.y}
  \item{QFA.x}{QFA.x}
  \item{QFA.NoORF}{QFA.NoORF}
  \item{QFA.NoTIME}{QFA.NoTIME}
  \item{PRIORS}{PRIORS}
  \item{TUNING}{TUNING}
}
\value{
SHM output
}
\keyword{qfaBayes}
