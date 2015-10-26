#include "Amumu/VariousFunctions/interface/VariousFunctions.h"
#include <math.h>
#include "TH1F.h"
#include "THistPainter.h"
#include "DataFormats/Math/interface/deltaPhi.h"

reco::GenParticleRef  VariousFunctions::findDaughterInDaughters(const reco::GenParticleRef& mother, const double pdgId, const bool abs)
{
  unsigned int iDaughters = 0;
  reco::GenParticleRef  found;
  reco::GenParticleRef childRef;
  if(abs)
  {
    while (iDaughters < mother->numberOfDaughters())
    {
      childRef = mother->daughterRef(iDaughters);
      if (fabs(childRef->pdgId()) == pdgId)
      {
	found = childRef;
        break;
      }//if fabs childRef
      iDaughters++;
    }//for iGenDaughters
  }//ifabs
 else 
  { 
    while (iDaughters < mother->numberOfDaughters())
    { 
      childRef = mother->daughterRef(iDaughters);
      if (childRef->pdgId() == pdgId)
      { 
        found = childRef;
        break;
      }//if fabs childRef
      iDaughters++;
    }//for iGenDaughters
  }//else
  return found;
}//findDaughter


bool VariousFunctions::findIfInDaughters(const reco::GenParticleRef& mother, const double pdgId, const bool abs)
{
  unsigned int iDaughters = 0;
  bool found = false;
  reco::GenParticleRef childRef;
  if(abs)
  {
    while (iDaughters < mother->numberOfDaughters())
    {
      childRef = mother->daughterRef(iDaughters);
      if (fabs(childRef->pdgId()) == pdgId)
      {
        found = true;
        break;
      }//if fabs childRef
      iDaughters++;
    }//for iGenDaughters
  }//ifabs
 else
  {
    while (iDaughters < mother->numberOfDaughters())
    {
      childRef = mother->daughterRef(iDaughters);
      if (childRef->pdgId() == pdgId)
      {
        found = true;
        break;
      }//if fabs childRef
      iDaughters++;
    }//for iGenDaughters
  }//else
  return found;
}//findDaughter
//decay products of A
   

