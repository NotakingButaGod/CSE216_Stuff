import Data.List.Split
import System.Exit
import System.Random
import Data.Array.IO
import Control.Monad
import System.IO.Unsafe
import Data.List
import Data.Maybe
import Data.Char
{-| this function should take in an integer and should create and return a string that displays the equivalent x.x.x.x IP
address representation of that number. -}
numToIpAddress :: Int -> String
numToIpAddress number = show ((number `div` 256 `div` 256 `div` 256) `mod` 256) ++ "."
            ++  show ((number `div` 256 `div` 256) `mod` 256) ++ "."
            ++ show ((number `div` 256) `mod` 256) ++ "."
            ++ show (number `mod` 256)

{-| ipAddressToNum 
this function should take in a string in the format of x.x.x.x representing a 32-bit ipv4 IP address and turn it into its
numeric equivalent as a single int, returning that value. -}
ipAddressToNum :: String -> Int
ipAddressToNum ipaddress = (read ((splitOn "." ipaddress) !! 0) :: Int) * (256 ^ 3)
                            + (read ((splitOn "." ipaddress) !! 1) :: Int) * (256 ^ 2)
                            + (read ((splitOn "." ipaddress) !! 2) :: Int) * (256 ^ 1)
                            + (read ((splitOn "." ipaddress) !! 3) :: Int) * (256 ^ 0)

{- this function should take no input but will generate a randomly ordered string of all the capital letters. This means it should
have a length of precisely 26. It should then return that string. Note that this key could then be used for both encryption and decryption.
Also note that it is up to you how to map the letters and numbers to indices. Meaning, in the key, the character found at index 0 should be
replaced for what other character? That is up to you and how you use it in your encrypt and decrypt methods. -}
randomnumber = [1,21,18,6,9,15,13,3,8,2,5,0,12,7,20,11,23,4,25,14,16,24,22,17,10,19] 
-- since professor says we can use hardcoded set of random number I guess I will just use it
generateKeyHelper :: [Char] -> [Int] -> Int -> Int -> [Char]
generateKeyHelper orign randomnumbers len index =
    if (len == 0)
        then do
            show ""
        else do
            return (orign !! (randomnumbers !! index)) ++ generateKeyHelper (orign) (randomnumbers) (len-1) (index+1)
testgenerateKeyHelper = init (init (generateKeyHelper "ABCDEFGHIJKLMNOPQRSTUVWXYZ" randomnumber (length ("ABCDEFGHIJKLMNOPQRSTUVWXYZ")) 0))

generateKey :: () -> String
generateKey () = do
    let input1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    let input2 = randomnumber
    let input3 = length input1
    let input4 = 0
    init (init (generateKeyHelper input1 input2 input3 input4))

{- this function should take a key string argument (like one produced by generateKey) and plaintext to encrypt. It should then return 
the produced ciphertext.-}
ultimateorigin = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
ultimatekey = "BCDEFGHIJKLMNOPQRSTUVWXYZA" -- change if you want to test different key

splitt = splitOn " " "not a king but a god"

ifstatement :: [Char] -> Bool
ifstatement input
    | null input == True = True
    | null input == False = False
testif = ifstatement (concat splitt)

anotherifstatement :: Bool -> [Char]
anotherifstatement input = 
    if input == False
        then show (splitt !! 0)
        else show " "
testanotherif = drop 1 (init (anotherifstatement testif))

testsplit1 = (splitOn " " "s a d s a d s a d a")
testsplit2 = concat (splitOn " " "s a d s a d s a d a")

testvalue = ultimatekey !! (fromJust $ elemIndex (toUpper ("not" !! 0)) ultimateorigin)

conversion :: [Char] ->[Char] -> Int -> Int -> [Char]
conversion string key len index =
    if (len == 0)
        then do
            show ""
        else do
            return (key !! (fromJust $ elemIndex (toUpper (string !! index)) ultimateorigin)) ++ (conversion (string) (key) (len-1) (index+1))

input1 = (splitOn " " "not a king but a god") !! 0
input2 = ultimatekey
input3 = length ((splitOn " " "not a king but a god") !! 0)
input4 = 0
conversioncheck = (init (init (conversion input1 input2 input3 input4)))

encrypthelper :: [Char] -> [Char] -> Int -> Int -> [[Char]]
encrypthelper string key len index =
    if(len == 0)
        then do
            return ""
        else do
            let input1 = (splitOn " " string) !! index 
            let input2 = key
            let input3 = length ((splitOn " " string) !! index)
            let input4 = 0
            return (init (init (conversion input1 input2 input3 input4))) ++ [" "] ++ (encrypthelper (string) (key) (len-1) (index+1))
i1 = ("not a king but a god")
i2 = ultimatekey
i3 = length (splitOn " " i1)
i4 = 0
testencryhelper =  concat (init (init (encrypthelper i1 i2 i3 i4)))

encrypt :: String -> String -> String
encrypt key plaintext = do
    let input1 = plaintext
    let input2 = key
    let input3 = length (splitOn " " input1)
    let input4 = 0
    concat (init (init (encrypthelper input1 input2 input3 input4)))

{- decrypt - this function should take as a key string argument (like one produced by generateKey) and ciphertext to decrypt. It should then
return the produced plaintext. Note that you should demonstrate your code working by combining use of both encrypt and decrypt using
the same keys.-}

conversion1 :: [Char] ->[Char] -> Int -> Int -> [Char]
conversion1 string key len index =
    if (len == 0)
        then do
            show ""
        else do
            return (key !! (fromJust $ elemIndex (toUpper (string !! index)) ultimatekey)) ++ (conversion1 (string) (key) (len-1) (index+1))

decrypthelper :: [Char] -> [Char] -> Int -> Int -> [[Char]]
decrypthelper string key len index =
    if(len == 0)
        then do
            return ""
        else do
            let input1 = (splitOn " " string) !! index 
            let input2 = key
            let input3 = length ((splitOn " " string) !! index)
            let input4 = 0
            return (init (init (conversion1 input1 input2 input3 input4))) ++ [" "] ++ (decrypthelper (string) (key) (len-1) (index+1))
            
decrypt :: String -> String -> String
decrypt original ciphertext = do
    let input1 = ciphertext
    let input2 = original
    let input3 = length (splitOn " " input1)
    let input4 = 0
    concat (init (init (decrypthelper input1 input2 input3 input4)))
    

numtoip1 = numToIpAddress 2130706433
numtoip2 = numToIpAddress 3221225984
iptonum1 = ipAddressToNum "127.0.0.1"
iptonum2 = ipAddressToNum "192.0.2.0"

original = ultimateorigin
key      = ultimatekey
plaintext = "NOTAKINGBUTAGOD"
ciphertext = "OPUBLJOHCVUBHPE"

test =  fromJust $ elemIndex 'A' ultimateorigin
test1 = plaintext !! (fromJust $ elemIndex 'A' ultimateorigin)
test2 = (splitOn " " plaintext)
testencrpt = encrypt key plaintext
testdecrypt = decrypt original ciphertext
testgenerateKey = generateKey ()

lasttest = 5 `div` 3
main = do
    putStrLn $ "Ipv4: " ++ show numtoip1
    putStrLn $ "Ipv4: " ++ show numtoip2
    putStrLn $ "Integer: " ++ show iptonum1
    putStrLn $ "Integer: " ++ show iptonum2
    putStrLn $ "test: " ++ show test
    putStrLn $ "test1: " ++ show test1
    putStrLn $ "test2: " ++ show test2
    putStrLn $ "testif: " ++ show testif
    putStrLn $ "testanotherif: " ++ show testanotherif
    putStrLn $ "testsplit1: " ++ show testsplit1
    putStrLn $ "testsplit2: " ++ show testsplit2
    putStrLn $ "testvalue: " ++ show testvalue
    putStrLn $ "input1: " ++ show input1
    putStrLn $ "input2: " ++ show input2
    putStrLn $ "input3: " ++ show input3
    putStrLn $ "conversioncheck: " ++ show conversioncheck
    putStrLn $ "testencryhelper: " ++ show testencryhelper
    putStrLn $ "testencrpt: " ++ show testencrpt
    putStrLn $ "testdecrypt: " ++ show testdecrypt
    putStrLn $ "testgenerateKeyHelper: " ++ show testgenerateKeyHelper
    putStrLn $ "testgenerateKey: " ++ show testgenerateKey
    putStrLn $ "lasttest: " ++ show lasttest
    

    
    
    






