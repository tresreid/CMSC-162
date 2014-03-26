import Data.Monoid
import Data.Maybe
import Data.List hiding (insert, delete)
{- This program finds the path from one side of an array to the other with the lowest sum. the array is denoted by a list of lists where the numbr of elements in the array is the number of rows in the array and the number of elements in each element of the array is the number of columns in the array. after creating the array, the function "finalbestpath" is used to find the value of the path with the lowest sum and the path itself. Additionally you can use the function "finalworstpath" to find the path with the highest value -}

data Tree a = Oblivion | Branch a (Tree a) (Tree a) (Tree a) -- data type for storing every path through the array
    deriving (Show) 
data Heap a = Empty | Node a (Heap a) (Heap a) -- data type for storing a single path though the array in arbitrary positions so that the sum can be taken	
    deriving (Show)

-- this funcion is used to cut the tree data type and add the path to the heap data type 
mktree :: (Ord a) => [Int] -> Heap a -> Tree a -> Heap a
mktree [x] newtree y = newtree
mktree (x:xs) newtree Oblivion = Empty
mktree (x:xs) newtree (Branch y a b c) 
       |(x==0) = mktree xs (insert newtree  (gettreeval a)) a
       |(x==1) = mktree xs (insert newtree  (gettreeval b)) b
       | otherwise = mktree xs (insert newtree (gettreeval c)) c

gettreeval :: Tree a -> Maybe a
gettreeval Oblivion = Nothing
gettreeval (Branch a x y z) = Just a

--reused old code to add values to the heap so that they can be summed later
insert :: (Ord a) => Heap a -> Maybe a -> Heap a
insert _ Nothing = Empty
insert Empty x = (Node (fromJust x) Empty Empty)	
insert (Node a b c) x   = (Node a (insert c x) b)	

getMax :: (Ord a) => Heap a -> Maybe a
getMax Empty = Nothing
getMax (Node x a b) = Just x

delete :: (Ord a) => Heap a -> Heap a
delete (Node _ Empty b) = b
delete (Node _ a Empty) = a
delete (Node _ a b)
    | (getMax a) >= (getMax b) = (Node (fromJust (getMax a)) (delete a) b)
    | (getMax a) <  (getMax b) = (Node (fromJust (getMax b)) (delete b) a)

heapToList :: (Ord a) => Heap a -> [a] -> [a]
heapToList Empty list = list
heapToList heap list = heapToList (delete heap) ((fromJust (getMax heap)):list)

--starting from one point on the far side, this function finds every possible path to the other side of the array,stopping just outside the array.
arraytotree :: [[a]] -> Tree a -> Int -> Int -> Tree a
arraytotree array tree@Oblivion index jndex 
	    |(jndex < 0) = tree
	    |(jndex == (length $ head array))= tree
	    |(index == (length array))= tree
 	    |otherwise = arraytotree array (Branch ((array !! index) !! jndex) Oblivion Oblivion Oblivion) index jndex
arraytotree array tree@(Branch a x y z) index jndex  
	    |(jndex < 0) = tree
	    |(jndex == (length $head array))= tree
	    |(index == (length array))= tree
	    |otherwise = Branch ((array !! index) !! jndex) (arraytotree array x (index+1) (jndex-1)) (arraytotree array y (index+1) (jndex)) (arraytotree array z (index+1) (jndex+1))
--stores every path from each starting point in the array. 
treeoflife :: [[a]] -> Int -> [Tree a] -> [Tree a]
treeoflife array i list
	   | (i == (length $head array)) = list
	   | otherwise = treeoflife array (i+1) (list++[arraytotree array Oblivion 0 i])

-- called for simplicity/readability. this list has length m 
truetree = treeoflife array 0 []


--makes each possible path from a starting point
mkpathlist array x n list
	   | (n== (length array)+1) = list
	   | otherwise  = mkpathlist array (quot x 3) (n+1) ((x `mod` 3) : list)

--makes each possible path
--superpathlist :: [[Int]] -> Int -> [[Int]] -> [[Int]]
superpathlist array x list
	      | x == (3^(length array)) = list
	      | otherwise = superpathlist array (x+1) (list ++ [mkpathlist array x 1 [] ])
--changes each possible tree path to a heap from a starting point
--woodchips :: Int -> Int -> [Heap a] -> [Heap a]
woodchips t l chips
	  | (l == (length $ superpathlist array 0 [])) = chips
	  | otherwise = woodchips t (l+1) (chips ++ [insert (mktree ((superpathlist array 0 []) !! l) Empty (truetree !! t)) (Just ((head array) !! t)) ]) 
-- changes each possible tree path to a heap
fullheap t list
	 | t == (length $ head array) = list
	 | otherwise = fullheap (t+1) (list++ (woodchips t 0 []))
--changes each heap to a list
fullheaptolist i list 
	       | i == ((length $ head array) * 3^(length array)) = list
	       | otherwise = fullheaptolist (i+1) (list ++ [heapToList ((fullheap 0 [])!! i) []])
--sums the each heap-list
sumall i list
       | (i== length (fullheaptolist 0 [])) = list
       | (length ((fullheaptolist 0 []) !! i) ==1) = sumall (i+1) (list ++ [[]])
       | otherwise = sumall (i+1) (list ++ [[sum (fullheaptolist 0 [] !! i)]])

allsums = sumall 0 []
reducedsum i list
	   | (i == length (fullheaptolist 0 [])) = list
	   | length (allsums !! i) == 0 = reducedsum (i+1) list
	   | otherwise = reducedsum (i+1) (list ++ (allsums !! i))
--finds the path with the lowest value
findbestsum = minimum (reducedsum 0 [])
--finds the path with the highest value
findworstsum = maximum (reducedsum 0 [])

findbestindex = elemIndex [(findbestsum)] (allsums)
findworstindex = elemIndex [(findworstsum)] (allsums)

beststartvalue i j
	       | (i > 3^(length array)) = beststartvalue (i-3^(length array)) (j+1)
	       | otherwise = (i,j)     
worststartvalue i j
	       | (i > 3^(length array)) = worststartvalue (i-3^(length array)) (j+1)
	       | otherwise = (i,j) 
findbestpath = mkpathlist array (fst (beststartvalue (fromJust findbestindex) 0) ) 1 [] 
findworstpath = mkpathlist array (fst (worststartvalue (fromJust findworstindex) 0) ) 1 [] 

bestpath i j list
	 | (j == (length array)) = list
	 | otherwise = bestpath ((i+ (findbestpath !! j)-1)) (j+1) (list ++ [(array !! j) !! i])
worstpath i j list
	 | (j == (length array)) = list
	 | otherwise = worstpath ((i+ (findworstpath !! j)-1)) (j+1) (list ++ [(array !! j) !! i])

finalbestpath = (findbestsum, (bestpath (snd (beststartvalue (fromJust findbestindex) 0)) 0 []))
finalworstpath = (findworstsum, (worstpath (snd (worststartvalue (fromJust findworstindex) 0)) 0 []))
array :: [[Int]]
array = [[-3,1,2,-2],[0,4,-2,3],[5,3,7,4],[-2,3,-4,0]] 