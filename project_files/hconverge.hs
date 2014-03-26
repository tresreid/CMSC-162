import Data.List

-- Takes a target value and the number of terms desired as arguments
-- and produces string of form "a_1 + a_2 + ... + a_n"
makeArrangement :: Double -> Int -> String
makeArrangement targetSum numTerms = makeSeries $ arrangedTerms targetSum numTerms

-- Converts a list of indices of terms of the harmonic series to a string
-- of the form "a_1 + ... + a_n"
makeSeries :: [Int] -> String
makeSeries [] = show 0
makeSeries [n] = "1/" ++ show n
makeSeries terms = ("1/" ++ (show $ head terms)) ++ " + " ++ (makeSeries $ tail terms)

-- Produces an arrangement of the alternating harmonic series 
-- in the form of a list of indices of terms
arrangedTerms :: Double -> Int -> [Int]
arrangedTerms _ 0 = []
arrangedTerms targetSum numTerms = termsSoFar ++ [nextTerm targetSum termsSoFar]
    where
        termsSoFar = arrangedTerms targetSum (numTerms - 1)

-- Add the positive terms in the series until the sum is greater than the target value,
-- Then add the negative terms until the sum is less than the target value, and so on.
nextTerm :: Double -> [Int] -> Int
nextTerm targetSum terms
    | remainder >= 0 = head $ [2,4..] \\ terms
    | remainder <  0 = head $ [1,3..] \\ terms
    where 
        remainder = targetSum - (sumSeries $ terms)

-- Computes a partial sum of a rearrangement of the alternating harmonic series
sumSeries :: [Int] -> Double
sumSeries = foldr (+) 0 . map harmonicTerm
    where
        -- Gives the nth term of the alternating harmonic series
        harmonicTerm n = (-1)^n * 1/(fromIntegral n)
    