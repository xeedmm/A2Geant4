// Abstract file-based event generator
// Author: Dominik Werthmueller, 2018

#include "TMath.h"

#include "G4ParticleDefinition.hh"

#include "A2FileGenerator.hh"

//______________________________________________________________________________
A2FileGenerator::A2FileGenerator(const char* filename, EFileGenType type)
{
    // Constructor.

    // init members
    fType = type;
    fFileName = filename;
    fNEvents = 0;
}

//______________________________________________________________________________
void A2FileGenerator::A2GenParticle_t::SetCorrectMass()
{
    // Init the mass of the particle based on the particle definition and
    // the 4-momentum.

    // check for defined massless particles
    if (fDef && fDef->GetPDGMass() == 0)
        fM = 0;
    else
        fM = TMath::Sqrt(fE*fE - fP.mag2());
}

//______________________________________________________________________________
void A2FileGenerator::A2GenParticle_t::Print(const char* pre) const
{
    // Print the content of this class.

    G4cout << pre << "Name                : " << (fDef ? fDef->GetParticleName() : "unknown") << G4endl
           << pre << "Momentum            : " << fP << G4endl
           << pre << "Energy              : " << fE << G4endl
           << pre << "Mass                : " << fM << G4endl
           << pre << "Vertex              : " << fX << G4endl
           << pre << "Vertex time         : " << fT << G4endl
           << pre << "Is tracked          : " << (fIsTrack ? "yes" : "no") << G4endl;
}

//______________________________________________________________________________
void A2FileGenerator::SetParticleIsTrack(G4int p, G4bool t)
{
    // Set the tracking flag for the particle 'p'.

    // check if particle can be tracked
    if (t && !fPart[p].fDef)
        return;

    fPart[p].fIsTrack = t;
}

//______________________________________________________________________________
void A2FileGenerator::Print() const
{
    // Print the content of this class.

    G4String type;
    if (fType == kMkin)
        type = "Mkin";
    else if (fType == kPluto)
        type = "Pluto";
    else if (fType == kPlutoCocktail)
        type = "Pluto Cocktail";
    else
        type = "Unknown";

    G4cout << "Generator type      : " << type << G4endl
           << "File name           : " << fFileName << G4endl
           << "Number of events    : " << fNEvents << G4endl
           << "Number of particles : " << fPart.size() << G4endl
           << "Primary vertex      : " << fVertex << G4endl
           << "Beam particle" << G4endl;
    fBeam.Print("  ");
    for (G4int i = 0; i < (G4int)fPart.size(); i++)
    {
        G4cout << "Particle " << i+1 << G4endl;
        fPart[i].Print("  ");
    }
}
