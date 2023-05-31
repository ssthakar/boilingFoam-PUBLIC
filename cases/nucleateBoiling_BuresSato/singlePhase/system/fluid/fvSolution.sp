/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  1.7.0                                 |
|   \\  /    A nd           | Web:      www.OpenFOAM.com                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "system";
    object      fvSolution;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

solvers
{
	//Needed for implicit solve of alpha1 in phase change code
    "alpha.liquid.*"
    {
        nAlphaCorr      1;  //2; dambreak
        nAlphaSubCycles 3;  //1; dambreak
        cAlpha          1;
        alphaApplyPrevCorr no;  // Apply the compression correction from the previous iteration
                                // Improves efficiency for steady-simulations but can only be applied
                                // once the alpha field is reasonably steady, i.e. fully developed

        MULESCorr       no;
        nLimiterIter    5;
        isoAdvection true;


        solver          smoothSolver;
        smoother        symGaussSeidel;
        tolerance       1e-8;
        relTol          0;
    };

    p_rgh
    {
        solver          GAMG;
        tolerance       1e-7;
        relTol          0.01;
        smoother        DICGaussSeidel;
        nPreSweeps      0;
        nPostSweeps     2;
        cacheAgglomeration true;
        agglomerator    faceAreaPair;
        mergeLevels     1;
        nCellsInCoarsestLevel 10;
    };

     p_rghFinal
    {
        solver          PCG;
        preconditioner
        {
            preconditioner  GAMG;

            tolerance       1e-8;
            relTol          0;

            nVcycles        2;

            smoother        DICGaussSeidel;
            nPreSweeps      0;
            nPostSweeps     2;
            nFinestSweeps   2;

            cacheAgglomeration true;
            nCellsInCoarsestLevel 10;
            agglomerator    faceAreaPair;
            mergeLevels     1;
        };
        tolerance       1e-9;
        relTol          0;
    };

    "pcorr.*"
    {
        $p_rgh;
        relTol          0;
    };


    "U.*"
    {
        solver          smoothSolver;
        smoother        symGaussSeidel;
        tolerance       1e-7;
        relTol          0;
    };

    /*
    "T.*"
    {
        solver          smoothSolver;
        smoother        symGaussSeidel;
        tolerance       1e-7;
        relTol          0.0;
    }
*/

    "T.*"
    {
        solver          PBiCG;
        preconditioner        DILU;
        tolerance       1e-10;
        relTol          0.0;
    }

    "mDot.*"
    {
        solver          PCG;
        preconditioner  DIC;
        tolerance       1e-10;
        relTol          1e-3;
    }


}

PIMPLE
{
    momentumPredictor   yes;
    nCorrectors         3;
    nNonOrthogonalCorrectors 1;
    frozenFlow true;
    //pRefPoint (0.000999 0 0.000001);
    //pRefValue 100000;

}

relaxationFactors
{
    "U.*"                      1;
}


// ************************************************************************* //
