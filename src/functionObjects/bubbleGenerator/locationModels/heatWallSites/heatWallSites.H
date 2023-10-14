
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2014 OpenFOAM Foundation
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

Class
    Foam::locationModels::fixedSites

Description
    Specify the sites as a vectorField.

SourceFiles
    fixedSites.C

\*---------------------------------------------------------------------------*/

#ifndef heatWallSites_H
#define heatWallSites_H

#include "List.H"
#include "bubbleGenerator/locationModels/fixedSites/fixedSites.H"
#include "fileName.H"
#include "fvMesh.H"
#include "locationModel.H"
#include "typeInfo.H"

namespace Foam
{
// forward declaration of class
class phasePair;

namespace locationModels
{

/*---------------------------------------------------------------------------*\
                           Class heatWallSites Declaration
\*---------------------------------------------------------------------------*/

class heatWallSites
:
  public locationModel
{
  //- location of all points that could serve as nucleation sites
  vectorField sites_;
  
  // list of boundary patches that can serve as nucleation sites
  const wordList  patchNames_;

  // patch index of patches that can serve as nucleation sites
  labelList patchIndex_;
  
  public:

      //- RunTime type information
    TypeName("heatWallSites");
    
      heatWallSites
      (
        const dictionary dict,
        const fvMesh &mesh
      );

    //- Destructor
    virtual ~heatWallSites();
    
    //- Member functions
    //- return sites for nucleation  
    virtual const vectorField & sites() const;
    
    void writeSites();

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // end of namespace location models 
} // end of namespace foam

#endif
