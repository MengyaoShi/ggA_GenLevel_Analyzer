#ifndef BBA_VariousFunctions_interface_VariousFunctions_h
#define BBA_VariousFunctions_interface_VariousFunctions_h

#include <vector>
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TAxis.h"
#include <string>
#include "TH2F.h"

class VariousFunctions { 

  public:
    static reco::GenParticleRef findDaughterInDaughters(const reco::GenParticleRef& , const double, const bool);
    static bool findIfInDaughters(const reco::GenParticleRef& , const double, const bool);

};
#endif
