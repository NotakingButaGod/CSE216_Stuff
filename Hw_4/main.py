import unittest
import random
from collections import OrderedDict

class IPAddressConverter:
    
    def __init__(self,inputaddress="",inputnumber=0):
        self.inputaddress = inputaddress
        self.inputnumber = inputnumber
        
    def numToIpAddress(self,inputnumber):
        ipaddress = str((inputnumber // 256 // 256 // 256) % 256) + "." \
        + str((inputnumber // 256 // 256 ) % 256) + "." \
        + str((inputnumber // 256) % 256) + "." \
        + str((inputnumber) % 256)
        
        return ipaddress
        
    def ipAddressToNum(self,inputaddress):
        number = int(inputaddress.split(".")[0]) * pow(256,3) \
        + int(inputaddress.split(".")[1]) * pow(256,2) \
        + int(inputaddress.split(".")[2]) * pow(256,1) \
        + int(inputaddress.split(".")[3]) * pow(256,0) 
        
        return number
    

class IPAddressConverterTest(unittest.TestCase):
    
    def numToIpAddress_Test(self):
        self.assertEqual(IPAddressConverter().numToIpAddress(2130706433),"127.0.0.1") #1
        self.assertEqual(IPAddressConverter().numToIpAddress(3221225984),"192.0.2.0") #2
        self.assertEqual(IPAddressConverter().numToIpAddress(1677787393),"100.1.1.1") #3
        self.assertEqual(IPAddressConverter().numToIpAddress(2130771969),"127.1.0.1") #4
        self.assertEqual(IPAddressConverter().numToIpAddress(2130772225),"127.1.1.1") #5
        self.assertEqual(IPAddressConverter().numToIpAddress(2130772226),"127.1.1.2") #6
        self.assertEqual(IPAddressConverter().numToIpAddress(2885746946),"172.1.1.2") #7
        self.assertEqual(IPAddressConverter().numToIpAddress(2896953602),"172.172.1.2") #8
        self.assertEqual(IPAddressConverter().numToIpAddress(2897010178),"172.172.222.2") #9
        self.assertEqual(IPAddressConverter().numToIpAddress(2897010302),"172.172.222.126") #10
        print("numToIpAddress_Test : pass 10")
    
    def ipAddressToNum_Test(self):
        self.assertEqual(IPAddressConverter().ipAddressToNum("127.0.0.1"),2130706433) #1
        self.assertEqual(IPAddressConverter().ipAddressToNum("192.0.2.0"),3221225984) #2
        self.assertEqual(IPAddressConverter().ipAddressToNum("100.1.1.1"),1677787393) #3
        self.assertEqual(IPAddressConverter().ipAddressToNum("127.1.0.1"),2130771969) #4
        self.assertEqual(IPAddressConverter().ipAddressToNum("127.1.1.1"),2130772225) #5
        self.assertEqual(IPAddressConverter().ipAddressToNum("127.1.1.2"),2130772226) #6
        self.assertEqual(IPAddressConverter().ipAddressToNum("172.1.1.2"),2885746946) #7
        self.assertEqual(IPAddressConverter().ipAddressToNum("172.172.1.2"),2896953602) #8
        self.assertEqual(IPAddressConverter().ipAddressToNum("172.172.222.2"),2897010178) #9
        self.assertEqual(IPAddressConverter().ipAddressToNum("172.172.222.126"),2897010302) #10
        print("ipAddressToNum_Test : pass 10")

class MonoalphabeticCipher:
    def __init__(self,originalkey="", key="",plaintext="",ciphertext="",length=0,index=0):
        self.plaintext = plaintext
        self.key = key
        self.ciphertext = ciphertext
        self.originalkey = originalkey
    
    def generateKey(self):
        key = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"
        key = key.split(" ")
        key = random.sample(key,26)
        key = "".join(key)
        return key
       
    def endehelper(self,originalkey,key,plaintext,length,index):
        if(length == 0):
            return ""
        else:
            if((plaintext)[index] == " "):
                return " " + self.endehelper(originalkey,key,plaintext,length-1,index+1) 
            else:
                return key[originalkey.index((plaintext)[index].upper())] + self.endehelper(originalkey,key,plaintext,length-1,index+1)   
            
    def encrypt(self,key,plaintext):
        origin = ("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z").split(" ")
        if(key == ""):
            key = self.generateKey()
        output = self.endehelper(origin,key,plaintext,len(plaintext),0)
        return output
        
    def decrypt(self,key,ciphertext):
        origin = ("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z").split(" ")
        if(key == ""):
            key = self.generateKey()
        output = self.endehelper(key,origin,ciphertext,len(ciphertext),0)
        return output
    
class MonoalphabeticCipherTest(unittest.TestCase):
    def generateKey_Test(self):
        # test 1: 
        key1 = MonoalphabeticCipher().generateKey()
        #print(key1)
        assert len(key1)==26 and "".join(OrderedDict.fromkeys(key1)) == key1 and key1.upper() == key1, "key1 failed to maintain the properties of cipher key"
                                    # this is to test duplicates                 # this is to test upper case
        # test 2:
        key2 = MonoalphabeticCipher().generateKey()
        #print(key2)
        assert len(key2)==26 and "".join(OrderedDict.fromkeys(key2)) == key2 and key2.upper() == key2, "key2 failed to maintain the properties of cipher key"
        # test 3:
        key3 = MonoalphabeticCipher().generateKey()
        #print(key3)
        assert len(key3)==26 and "".join(OrderedDict.fromkeys(key3)) == key3 and key3.upper() == key3, "key3 failed to maintain the properties of cipher key"
        # test 4:
        key4 = MonoalphabeticCipher().generateKey()
        #print(key4)
        assert len(key4)==26 and "".join(OrderedDict.fromkeys(key4)) == key4 and key4.upper() == key4, "key4 failed to maintain the properties of cipher key"
        # test 5:
        key5 = MonoalphabeticCipher().generateKey()
        #print(key5)
        assert len(key5)==26 and "".join(OrderedDict.fromkeys(key5)) == key5 and key5.upper() == key5, "key5 failed to maintain the properties of cipher key"
        # test 6:
        key6 = MonoalphabeticCipher().generateKey()
        #print(key6)
        assert len(key6)==26 and "".join(OrderedDict.fromkeys(key6)) == key6 and key6.upper() == key6, "key6 failed to maintain the properties of cipher key"
        # test 7:
        key7 = MonoalphabeticCipher().generateKey()
        #print(key7)
        assert len(key7)==26 and "".join(OrderedDict.fromkeys(key7)) == key7 and key7.upper() == key7, "key7 failed to maintain the properties of cipher key"
        # test 8:
        key8 = MonoalphabeticCipher().generateKey()
        #print(key8)
        assert len(key8)==26 and "".join(OrderedDict.fromkeys(key8)) == key8 and key8.upper() == key8, "key8 failed to maintain the properties of cipher key"
        # test 9:
        key9 = MonoalphabeticCipher().generateKey()
        #print(key9)
        assert len(key9)==26 and "".join(OrderedDict.fromkeys(key9)) == key9 and key9.upper() == key9, "key9 failed to maintain the properties of cipher key"
        # test 10:
        key10 = MonoalphabeticCipher().generateKey()
        #print(key10)
        assert len(key10)==26 and "".join(OrderedDict.fromkeys(key10)) == key10 and key10.upper() == key10, "key10 failed to maintain the properties of cipher key"
        
        print("generateKey_Test: pass 10")
    
    def encrypt_Test(self):
        # test1 : takes in assigned key and plaintext and produce the right ciphertext
        self.assertEqual(MonoalphabeticCipher().encrypt("BCDEFGHIJKLMNOPQRSTUVWXYZA","NOTAKINGBUTAGODWENTAOHE"), "OPUBLJOHCVUBHPEXFOUBPIF")
        # test2: take in empty space, should produce empty space
        self.assertEqual(MonoalphabeticCipher().encrypt("BCDEFGHIJKLMNOPQRSTUVWXYZA",""), "")
        # test3: takes in assigned key and single letter, should produce the right single ciphertext letter 
        self.assertEqual(MonoalphabeticCipher().encrypt("BCDEFGHIJKLMNOPQRSTUVWXYZA","N"), "O")
        # test4: take in different assigned key
        origin1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key1 =    "WENMPBZIGDAKXFQUVLOHTRJYCS"
        self.assertEqual(MonoalphabeticCipher().encrypt(key1,""), "")
        self.assertEqual(MonoalphabeticCipher().encrypt(key1,"N"), "F")
        self.assertEqual(MonoalphabeticCipher().encrypt(key1,"NOTAKINGBUTAGOD"), "FQHWAGFZETHWZQM")
        # test5: take in different assigned key
        origin2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key2 =    "NFVWBCQULJXEHDMGSIKPAZYOTR"
        self.assertEqual(MonoalphabeticCipher().encrypt(key2,""), "")
        self.assertEqual(MonoalphabeticCipher().encrypt(key2,"N"), "D")
        self.assertEqual(MonoalphabeticCipher().encrypt(key2,"NOTAKING"), "DMPNXLDQ")
        # test6: take in different assigned key
        origin3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key3 =    "LRTDVOEPYAFSHGWBJKNCZIXQMU"
        self.assertEqual(MonoalphabeticCipher().encrypt(key3,""), "")
        self.assertEqual(MonoalphabeticCipher().encrypt(key3,"N"), "G")
        self.assertEqual(MonoalphabeticCipher().encrypt(key3,"NOTAKING"), "GWCLFYGE")
        # test7: take in different assigned key
        origin4 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key4 =    "SPNMKDUVBJOTQGAIWRLFHYZCEX"
        self.assertEqual(MonoalphabeticCipher().encrypt(key4,""), "")
        self.assertEqual(MonoalphabeticCipher().encrypt(key4,"H"), "V")
        self.assertEqual(MonoalphabeticCipher().encrypt(key4,"WENTAOHE"), "ZKGFSAVK")
        # test8: take in different assigned key
        origin5 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key5 =    "YRBFMOQDXLEIKPNJGWCAHZSTVU"
        self.assertEqual(MonoalphabeticCipher().encrypt(key5,""), "")
        self.assertEqual(MonoalphabeticCipher().encrypt(key5,"I"), "X")
        self.assertEqual(MonoalphabeticCipher().encrypt(key5,"IMSORRY"), "XKCNWWV")
        # test9: take in different assigned key
        origin6 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key6 =    "ZHRSGUTFXVPCNYLWAJDMOBIEKQ"
        self.assertEqual(MonoalphabeticCipher().encrypt(key6,""), "")
        self.assertEqual(MonoalphabeticCipher().encrypt(key6,"W"), "I")
        self.assertEqual(MonoalphabeticCipher().encrypt(key6,"IMTRASH"), "XNMJZDF")
        # test10: take in different assigned key
        origin7 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key7 =    "CVEHFIGLWKMYOAUZSRJQDNBTPX"
        self.assertEqual(MonoalphabeticCipher().encrypt(key7,""), "")
        self.assertEqual(MonoalphabeticCipher().encrypt(key7,"T"), "Q")
        self.assertEqual(MonoalphabeticCipher().encrypt(key7,"SHOULDIDIE"), "JLUDYHWHWF")
        
        print("encrypt_Test: pass 10")
        
    def decrypt_Test(self):
        # test1 : takes in assigned key and ciphertext and produce the right plaintext
        self.assertEqual(MonoalphabeticCipher().decrypt("BCDEFGHIJKLMNOPQRSTUVWXYZA","OPUBLJOHCVUBHPEXFOUBPIF"), "NOTAKINGBUTAGODWENTAOHE")
        # test2: take in empty space, should produce empty space
        self.assertEqual(MonoalphabeticCipher().decrypt("BCDEFGHIJKLMNOPQRSTUVWXYZA",""), "")
        # test3: takes in assigned key and single letter, should produce the right single plaintext letter 
        self.assertEqual(MonoalphabeticCipher().decrypt("BCDEFGHIJKLMNOPQRSTUVWXYZA","O"), "N")
        # test4: take in different assigned key
        origin1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key1 =    "WENMPBZIGDAKXFQUVLOHTRJYCS"
        self.assertEqual(MonoalphabeticCipher().decrypt(key1,""), "")
        self.assertEqual(MonoalphabeticCipher().decrypt(key1,"F"), "N")
        self.assertEqual(MonoalphabeticCipher().decrypt(key1,"FQHWAGFZETHWZQM"), "NOTAKINGBUTAGOD")
        # test5: take in different assigned key
        origin2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key2 =    "NFVWBCQULJXEHDMGSIKPAZYOTR"
        self.assertEqual(MonoalphabeticCipher().decrypt(key2,""), "")
        self.assertEqual(MonoalphabeticCipher().decrypt(key2,"D"), "N")
        self.assertEqual(MonoalphabeticCipher().decrypt(key2,"DMPNXLDQ"), "NOTAKING")
        # test6: take in different assigned key
        origin3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key3 =    "LRTDVOEPYAFSHGWBJKNCZIXQMU"
        self.assertEqual(MonoalphabeticCipher().decrypt(key3,""), "")
        self.assertEqual(MonoalphabeticCipher().decrypt(key3,"G"), "N")
        self.assertEqual(MonoalphabeticCipher().decrypt(key3,"GWCLFYGE"), "NOTAKING")
        # test7: take in different assigned key
        origin4 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key4 =    "SPNMKDUVBJOTQGAIWRLFHYZCEX"
        self.assertEqual(MonoalphabeticCipher().decrypt(key4,""), "")
        self.assertEqual(MonoalphabeticCipher().decrypt(key4,"V"), "H")
        self.assertEqual(MonoalphabeticCipher().decrypt(key4,"ZKGFSAVK"), "WENTAOHE")
        # test8: take in different assigned key
        origin5 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key5 =    "YRBFMOQDXLEIKPNJGWCAHZSTVU"
        self.assertEqual(MonoalphabeticCipher().decrypt(key5,""), "")
        self.assertEqual(MonoalphabeticCipher().decrypt(key5,"X"), "I")
        self.assertEqual(MonoalphabeticCipher().decrypt(key5,"XKCNWWV"), "IMSORRY")
        # test9: take in different assigned key
        origin6 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key6 =    "ZHRSGUTFXVPCNYLWAJDMOBIEKQ"
        self.assertEqual(MonoalphabeticCipher().decrypt(key6,""), "")
        self.assertEqual(MonoalphabeticCipher().decrypt(key6,"I"), "W")
        self.assertEqual(MonoalphabeticCipher().decrypt(key6,"XNMJZDF"), "IMTRASH")
        # test10: take in different assigned key
        origin7 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        key7 =    "CVEHFIGLWKMYOAUZSRJQDNBTPX"
        self.assertEqual(MonoalphabeticCipher().decrypt(key7,""), "")
        self.assertEqual(MonoalphabeticCipher().decrypt(key7,"Q"), "T")
        self.assertEqual(MonoalphabeticCipher().decrypt(key7,"JLUDYHWHWF"), "SHOULDIDIE")
        
        print("decrypt_Test: pass 10")
        

if __name__ == "__main__":
    print("hello world")
   
    test1 = IPAddressConverterTest()
    test1.numToIpAddress_Test()
    test1.ipAddressToNum_Test()
    
    test2 = MonoalphabeticCipherTest()
    test2.generateKey_Test()
    test2.encrypt_Test()
    test2.decrypt_Test()
    
    
    


