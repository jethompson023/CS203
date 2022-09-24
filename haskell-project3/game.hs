module Main where
import System.Environment
import System.IO
import System.Directory
import Data.Maybe
import Data.Char
import Data.List
import Text.Read
import Control.Arrow (ArrowChoice(right))

data BSTode = MTnode |
                Node BSTode WordFamily BSTode deriving (Show)

emptyTree = MTnode

--insertTree inserts words into families stored in the search tree. 
--Search key is the pattern of word (and families)
insertTree :: BSTnode -> Pattern -> String -> BSTnode
insertTree MTnode pattern word = Node MTnode (Family pattern [word] 1) MTnode
insertTree (Node left fam right) pattern word
    | pat fam > pattern = Node (insertTree left pattern word) fam right
    | pat fam < pattern = Node left fam (insertTree right pattern word)
    | otherwise = Node left (Family pattern (wrd : (dictWords fam)) ((size fam) + 1)) right

-- usage message if command line arguments when running program are wrong.
usage progName = "Usage: " ++ progName ++ "Dictionary word guesses" ++
        "\n length of word must be between 3 and 10"

-- Pattern is the current String of found and not-found letters of word
type Pattern = String 

--WordFamily consists of the current word pattern, all words fitting that pattern,
--  and the number of words in the family

data WordFamily = Family {
    pat :: Pattern,
    dictWords :: [String],
    size :: Int
} deriving (Show)


emptyFam = Family "" [] 0 -- this WordFamily is empty!

--apply read to a String to get an Int
readInt :: String -> Int
readInt = read

--get the name of the dictionary or Nothing,
--  note, if the number of command line args is wrong, get Nothing
getName :: [String] -> Maybe String
getName list
  | length list < 3                = Nothing
  | length list > 4                = Nothing
  | x <- doesFileExist (head list) = Just (head list)
  | otherwise                      = Nothing

