/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "className.H"
#include "dictionary.H"
#include "fvMesh.H"
#include "heatWallSites.H"
#include "addToRunTimeSelectionTable.H"
#include "locationModel.H"
#include "stdFoam.H"
#include "IOobject.H"
#include "Time.H"

// static stuff
namespace Foam
{
namespace locationModels
{
  defineTypeNameAndDebug(heatWallSites,0);
  addToRunTimeSelectionTable(locationModel, heatWallSites, dictionary);

} //end of locationModels 
} //end of Foam

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
Foam::locationModels::heatWallSites::heatWallSites
(
  const dictionary dict,
  const fvMesh& mesh
)
:
  locationModel(dict,mesh),
  patchNames_(dict.lookup("patchNames"))
{
  // read patches from dict and store their indexes in the patch index list
  for(word patchName : patchNames_)
  {
    const label patchIndex = mesh.boundaryMesh().findPatchID(patchName);
    if(patchIndex != -1)
    {
      patchIndex_.append(patchIndex);
    }
    else  
    {
      Info<<"Error: Patch "<< patchName << " not Found "<< endl;
    }
  }

  // populate sites
  forAll(patchIndex_, patchID)
  {
    const polyPatch & bPatch = mesh.boundaryMesh()[patchID];
    forAll(bPatch,faceID)
    {
      // get face centers as nucleation sites 
      sites_.append(bPatch.faceCentres()[faceID]);
    }
  }

  IOobject faceCentersIO
  (
    "faceCenterr",
    mesh,
    runTime.constant(),
    IOobject::NO_READ,
    IOobject::AUTO_WRITE
  );
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //
Foam::locationModels::heatWallSites::~heatWallSites()
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const Foam::vectorField& Foam::locationModels::heatWallSites::sites() const
{
  return sites_;
}

// ************************************************************************* //

