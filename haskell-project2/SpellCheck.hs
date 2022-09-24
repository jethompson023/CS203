{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
import Data.Char
import System.Environment
import System.IO
import Data.List
import Data.Bool (bool)
import Text.XHtml (input)

docParser :: String -> [String]
docParser = lines

lineNumber :: [String] -> Int -> [(String, Int)]
lineNumber [] _ = []
lineNumber (x:xs) ln = (x, ln) : lineNumber xs (ln + 1)

wordGrab :: String -> String
wordGrab [] = [] --base case
wordGrab (x:xs)
  | isLetter x = x : wordGrab xs --if the first character is a letter, add it to the list and recurse
  | otherwise = ' ' : wordGrab xs --otherwise, add a space to the list and recurse

wordNumber :: [(String, Int)] -> [([String], Int)]
wordNumber []  = []
wordNumber ((str, num):xs) = (words (wordGrab str), num) : wordNumber xs

wordList :: [([String], Int)] -> [([(String, Int)], Int)]
wordList [] = []
wordList ((w, ln) : xs) = (lineNumber w 1, ln) : wordList xs

{-
    wordTriple: Recieves the list of tuples with a line number and
    returns a list of tuples with the word and line number

    Input Format: [([(String, Int)], Int)]
    Output Format: [(word, line number, word number)]
-}
wordTriple :: [([(String, Int)], Int)] -> [(String, Int, Int)]
wordTriple [] = []
wordTriple ((xs, ln) : xss) = map (\(x, y) -> (x, ln, y)) xs ++ wordTriple xss

docTransform :: String -> [(String, Int, Int)]
docTransform input = wordTriple(wordList(wordNumber(lineNumber (lines input )1)))

spellCheck :: [(String, Int, Int)] -> [String] -> [(String, Int, Int, Bool)]
spellCheck [] _ = []
--case 1: where the document ends -> end the program
--case 2: if the dictionary runs out -> then all document words are incorrect
spellCheck ((xs, ln, wn) : xss) [] = (xs, ln, wn, False) : spellCheck xss []
spellCheck ((xs, ln, wn) : xss) (y : ys)
  | xs == y = (xs, ln, wn, True) : spellCheck xss (y : ys)
  | xs > y = spellCheck ((xs, ln, wn) : xss) ys
  | xs < y = (xs, ln, wn, False) : spellCheck xss (y : ys)

resultTransform :: [(String, Int, Int, Bool)] -> [String]
resultTransform [] = []
resultTransform ((xs, ln, wn, False) : xss) = ("\t\t" ++ xs ++ " Incorrect wordNumber : " ++ (show wn) ++ " lineNumber: " ++ (show ln)) : resultTransform xss
resultTransform ((xs, ln, wn, True) : xss) = ( xs ++ " Correct wordNumber : " ++ (show wn) ++ " lineNumber: " ++ (show ln)) : resultTransform xss


--Takes first document file then dictionary file
--As input then takes third argument as output file
--For results of spell checking document file
main = do
  [inFile, dictFile, outFile] <- getArgs
  input <- readFile inFile
  dict <- readFile dictFile
  let dictionary = words dict
  let input_transform = docTransform input
  let spellCheckResults = spellCheck input_transform dictionary
  let results = unlines (resultTransform spellCheckResults)
  writeFile outFile results