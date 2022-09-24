--Jeremiah Thompson
--CS 231 - Project 1
--Haskell Project 1: 


module DocTransformer where

import Data.Char
import Data.List

--transformDoc is our main funciton that will tie back into the main program
--it takes in a list of strings as an input and returns a list of strings
transformDoc :: String -> Int -> String
transformDoc input size = caseWorker $ unlines $ reverse $ lengthCheck (words $wordGrab input) size 

--wordGrab takes in a string and returns a list of strings
wordGrab :: String -> String
wordGrab [] = [] --base case
wordGrab (x:xs)
  | isLetter x = x : wordGrab xs --if the first character is a letter, add it to the list and recurse
  | otherwise = ' ' : wordGrab xs --otherwise, add a space to the list and recurse

--lengthCheck takes in a list of strings and a size and returns a list of strings
lengthCheck :: [String] -> Int -> [String]
--filter the list of words to only those that are the same length as the listNum
lengthCheck wordList listNum = [w | w <- wordList, length w == listNum]

--This is our list of vowels we are going to look for when performing the case transformation in the caseWorker function.
vowels = "aeiouAEIOU"


--caseWorker is a helper function that will take the list of words and return a list of strings
caseWorker :: String -> String
caseWorker [] = [] --base case
caseWorker (x:xs)
  | x == '\n' = x : caseWorker xs --if the first character is a newline, add it to the list and recurse
  | x `elem` vowels = toUpper x : caseWorker xs --if the first character is a vowel, make it uppercase and recurse
  | otherwise = toLower x : caseWorker xs--otherwise, make it lowercase and recurse

