//To be put in src/finiteVolume/fields/fvPatchFields/derived 
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
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

#include "magnusBlade.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "fvcMeshPhi.H"


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::magnusBlade::
magnusBlade
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF),
    UName_("U"),
    axis_(vector::zero),
    tipV_(0)
{}


Foam::magnusBlade::
magnusBlade
(
    const magnusBlade& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper),
    UName_(ptf.UName_),
    axis_(ptf.axis_),
    tipV_(ptf.tipV_().clone().ptr())
{}


Foam::magnusBlade::
magnusBlade
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF),
    UName_(dict.lookupOrDefault<word>("U", "U")),
    axis_(dict.lookup("axis")),
    tipV_(DataEntry<scalar>::New("tipV", dict))
{
    fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
}


Foam::magnusBlade::
magnusBlade
(
    const magnusBlade& mwvpvf
)
:
    fixedValueFvPatchVectorField(mwvpvf),
    UName_(mwvpvf.UName_),
    axis_(mwvpvf.axis_),
    tipV_(mwvpvf.tipV_().clone().ptr())
{}


Foam::magnusBlade::
magnusBlade
(
    const magnusBlade& mwvpvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(mwvpvf, iF),
    UName_(mwvpvf.UName_),
    axis_(mwvpvf.axis_),
    tipV_(mwvpvf.tipV_().clone().ptr())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::magnusBlade::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const fvPatch& p = patch();
    const polyPatch& pp = p.patch();
    const fvMesh& mesh = dimensionedInternalField().mesh();
    const pointField& oldPoints = mesh.oldPoints();

    vectorField oldFc(pp.size());

    forAll(oldFc, i)
    {
        oldFc[i] = pp[i].centre(oldPoints);
    }

    const scalar t = this->db().time().timeOutputValue();
    scalar tipVelocity = tipV_->value(t);
    const vectorField n(p.nf());
    const vectorField Up
	(
	(pp.faceCentres() - oldFc)/mesh.time().deltaTValue() + tipVelocity*( n ^ (axis_/mag(axis_)) )
	);

    const volVectorField& U = db().lookupObject<volVectorField>(UName_);
    scalarField phip
    (
        p.patchField<surfaceScalarField, scalar>(fvc::meshPhi(U))
    );

    const scalarField& magSf = p.magSf();
    tmp<scalarField> Un = phip/(magSf + VSMALL);
    
//Up is velocity vector of mesh motion.
//Un is velocity magnitude normal to wall. (flux (velocity*patch area) divided by surface area).
//n is normal area vectors.
//n & Up is inner product of n and Up (velocity magnitude of Up along direction of n).
//Un - (n & Up) is velocity normal to wall 
    vectorField::operator=(Up + n*(Un - (n & Up)));

    fixedValueFvPatchVectorField::updateCoeffs();
}


void Foam::magnusBlade::write(Ostream& os) const
{
    fvPatchVectorField::write(os);
    writeEntryIfDifferent<word>(os, "U", "U", UName_);
    os.writeKeyword("axis") << axis_ << token::END_STATEMENT << nl;
    tipV_->writeData(os);
    writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        magnusBlade
    );
}

// ************************************************************************* //
