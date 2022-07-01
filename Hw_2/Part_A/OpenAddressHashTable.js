class KeyValuePair {
    constructor(initKey, initValue) {
        this.key = initKey;
        this.value = initValue;
    }
    
    toString() {
        return "(" + this.key + ", " + this.value.toString() + ")";
    }
}

export default class OpenAddressHashTable {
    constructor(initLength, initKeyLength) {
        this.length = initLength;
        this.size = 0;
        this.keyLength = initKeyLength;
        this.hashTable = [];
    }

    hashCode(key) {
        let charsSum = 0;
        for (let i = 0; i < key.length; i++) {
            let keyChar = key.charAt(i);
            let charAsNum = keyChar.charCodeAt(0);
            charsSum += charAsNum;
        }
        return charsSum % this.length;
    }

    generateKey() {
        let key = "";
        for (let i = 0; i < this.keyLength; i++) {
            let randomNum = Math.floor(Math.random() * 36);
            let randomChar;
            if (randomNum < 10) {
                randomNum += 48;
                randomChar = String.fromCharCode(randomNum);
            }
            else {
                randomNum += 55;
                randomChar = String.fromCharCode(randomNum);
            }
            key += randomChar;
        }
        return key;
    }
    
    // @todo - YOU MUST DEFINE THIS METHOD
    getValue(key) {
        let index = this.hashCode(key);
        let count = 0;
        while (count < this.length){
            if (this.hashTable[index] == null){
                return null;
            }
            else if(this.hashTable[index].key.localeCompare(key) === 0){
                return this.hashTable[index].value;
            }
            index++;
            if(index == this.length){
                index = 0;
            }
            count++;
        }
        return null;
    }
    
    // @todo - YOU MUST DEFINE THIS METHOD
    removeValue(key) {  
        let index = this.hashCode(key);
        let count = 0;
        while (count < this.length){
            if(this.hashTable[index] == null){
                return;
            }
            else if(this.hashTable[index].key.localeCompare(key) === 0){
                this.hashTable[index] = null;
                this.size--;

                let temp = [];
                let counter = 0;

                for(let i = 0; i < this.length; i++){
                    if(this.hashTable[i] != null){
                        temp[counter] = this.hashTable[i];
                        counter++;
                    }
                    this.hashTable[i] = null;
                }
                this.size = 0;
                for(let i = 0; i < counter ; i++){
                    let item = temp[i];
                    let keyToRehash = item.key;
                    let valueToRehash = item.value;
                    this.putValue(keyToRehash,valueToRehash);
                }
                return;
            }
            index++;
            if (index == this.length){
                index = 0;
            }
            count++;
        }
    }

    // @todo - YOU MUST DEFINE THIS METHOD
    putValue(key, item) {
        let index = this.hashCode(key);
        let count = 0;
        while (count < this.length){
            //let testKVP = this.hashTable[index];
            //console.log(testKVP);
            //console.log(this.key);
            if(this.hashTable[index] == null){
                this.hashTable[index] = new KeyValuePair(key,item);
                //console.log(this.hashTable[index].key);
                //console.log(this.hashTable[index].value);
                this.size++;
                return;
            }
            else if(this.hashTable[index].key.localeCompare(key) === 0){
                this.hashTable[index].value = item;
                this.size++; // I don't get why we need to add size here, isn't replacing canceling out the old one
                return;
            }
            index++;
            //console.log(index);
            if (index == this.length){
                index = 0;
                //console.log(this.length);
                //console.log(index);
            }
            count++;
        }
        let temp = this.hashTable;
        //console.log(temp[0].key);
        //console.log(temp[0].value);
        this.length = this.length*2;
        this.hashTable = [];
        for(let i = 0; i < length ; i++){
            this.hashTable[i] = null;
        }
        //console.log(temp[0].key);
        //console.log(temp[0].value);
        let numToCopy = this.size;
        //console.log(numToCopy);
        this.size = 0;
        for (let i = 0; i < numToCopy ; i++){
            let kvp = temp[i];
            let keyToMove = kvp.key;
            let valueToMove = kvp.value;
            this.putValue(keyToMove,valueToMove);
        }
        this.putValue(key,item);
    }
    
    toString() {
        let text = "[\n";
        for (let i = 0; i < this.length; i++) {
            let kvp = this.hashTable[i];
            let kvpDescription = "null";
            if (kvp != null) {
                kvpDescription = kvp.toString();
            }
            text += "   " + i + ": " + kvpDescription + "\n";
        }
        text += "]\n";
        return text;
    }
};