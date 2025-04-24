function stringToWordArray(str) {
  return CryptoJS.enc.Utf8.parse(str);
}

// Convert a WordArray object to a string
function wordArrayToString(wordArray) {
  return CryptoJS.enc.Utf8.stringify(wordArray);
}

// Pad the key if it's less than 16 characters
function padKey(key) {
  while (key.length < 16) {
    key += key;
  }
  return key.slice(0, 16);
}

function encrypt() {
  if ("AES" == document.getElementById("Algorithm").value) {
    var encrypted = CryptoJS.AES.encrypt(
      document.getElementById("MessageEncryption").value,
      document.getElementById("EncryptionKey").value
    );
    document.getElementById("Ciphertext").textContent = encrypted;
  } else if ("OTP" == document.getElementById("Algorithm").value) {
    const key = document.getElementById("EncryptionKey").value;
    const message = document.getElementById("MessageEncryption").value;
    console.log(message);
    let repeatedKey = "";
    for (let i = 0; i < message.length; i++) {
      repeatedKey += key[i % key.length];
    }

    // Perform OTP encryption
    let encrypted = "";
    for (let i = 0; i < message.length; i++) {
      let m = message.charCodeAt(i);
      let k = repeatedKey.charCodeAt(i);
      let c = String.fromCharCode(m ^ k); // XOR the message and the key
      encrypted += c;
    }
    document.getElementById("Ciphertext").textContent = encrypted;
  } else if ("3DES" == document.getElementById("Algorithm").value) {
    encryptText();
    // Convert a string to a WordArray object

    // Encrypt text using 3DES algorithm and the provided key
    function encryptText() {
      var inputText = document.getElementById("MessageEncryption").value;
      var key = padKey(document.getElementById("EncryptionKey").value);

      var encodedText = stringToWordArray(inputText);
      var encrypted = CryptoJS.AES.encrypt(encodedText, key, {
        mode: CryptoJS.mode.ECB,
      });

      var encryptedText = encrypted.toString();

      document.getElementById("Ciphertext").value = encryptedText;
    }

    // Decrypt text using 3DES algorithm and the provided key
  }
}
function decrypt() {
  if ("AES" == document.getElementById("Algorithm").value) {
    document.getElementById("MessageDecryption").textContent =
      document.getElementById("Ciphertext").textContent;
    var decrypted = CryptoJS.AES.decrypt(
      document.getElementById("MessageDecryption").value,
      document.getElementById("DecryptionKey").value
    ).toString(CryptoJS.enc.Utf8);
    document.getElementById("Plaintext").textContent = decrypted;
  } else if ("OTP" == document.getElementById("Algorithm").value) {
    document.getElementById("MessageDecryption").textContent =
      document.getElementById("Ciphertext").textContent;
    const key = document.getElementById("DecryptionKey").value;
    const message = document.getElementById("MessageDecryption").value;
    console.log(message);
    let repeatedKey = "";
    for (let i = 0; i < message.length; i++) {
      repeatedKey += key[i % key.length];
    }

    // Perform OTP encryption
    let decrypted = "";
    for (let i = 0; i < message.length; i++) {
      let m = message.charCodeAt(i);
      let k = repeatedKey.charCodeAt(i);
      let c = String.fromCharCode(m ^ k); // XOR the message and the key
      decrypted += c;
    }
    document.getElementById("Plaintext").textContent = decrypted;
  } else if ("3DES" == document.getElementById("Algorithm").value) {
    decryptText();
    document.getElementById("MessageDecryption").textContent =
      document.getElementById("Ciphertext").textContent;
    function decryptText() {
      var inputText = document.getElementById("MessageDecryption").value;
      var key = padKey(document.getElementById("DecryptionKey").value);

      var decrypted = CryptoJS.AES.decrypt(inputText, key, {
        mode: CryptoJS.mode.ECB,
      });

      var decryptedText = wordArrayToString(decrypted);

      document.getElementById("Plaintext").value = decryptedText;
    }
  }
}
