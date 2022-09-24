import Data.Char
import Data.List

transformDoc :: String -> Int -> String
transformDoc input size = caseWorker $ unlines $ reverse $ lengthCheck (words $wordGrab input) size

wordGrab :: String -> String
wordGrab [] = []
wordGrab (x:xs)
  | isLetter x = x : wordGrab xs
  | otherwise = ' ' : wordGrab xs

lengthCheck :: [String] -> Int -> [String]
lengthCheck wordList listNum = [w | w <- wordList, length w == listNum]

vowels = "aeiouAEIOU"

caseWorker :: String -> String
caseWorker [] = []
caseWorker (x:xs)
  | x == '\n' = x : caseWorker xs
  | x `elem` vowels = toUpper x : caseWorker xs
  | otherwise = toLower x : caseWorker xs

{-
  caseWorker $ unlines $ reverse $ lengthCheck (words $wordGrab "jeremiah&*#($gets**similar**functions**dogs") 4
  transformDoc :: String -> Int -> String 
  transformDoc input size = caseWorker $ unlines $ reverse $ lengthCheck (words $wordGrab input) size
  vowels = ['a', 'e', 'i', 'o', 'u'] || ['A', 'E', 'I', 'O', 'U']

  transformDoc :: String -> Int -> String 
  transformDoc input size = caseWorker $ unlines $ reverse $ lengthCheck (words $wordGrab input) size

  wordGrab :: String -> String
  wordGrab [] = []
  wordGrab (x:xs)
    | isLetter x = x : wordGrab xs
    | otherwise = ' ' : wordGrab xs

  lengthCheck :: [String] -> Int -> [String] 
  lengthCheck wordList listNum = [w | w <- wordList, length w == listNum] 

  vowels = "aeiouAEIOU"

  caseWorker :: String -> String
  caseWorker [] = []
  caseWorker (x:xs)
    | x == '\n' = x : caseWorker xs
    | elem x vowels =toUpper x : caseWorker xs
    | otherwise = toLower x : caseWorker xs
  
-}