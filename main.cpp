#include "main.h"

int main()
{
     // ------------------Signing process------------------

     // message to be transmitted along with a signature
     SetSeed(Z(0));
     string message = "Hello World";

     cout << '\n'
          << "The message is:" << '\n'
          << '\n'
          << message << '\n';

     cout << "----------------------------------------------------------------" << '\n';

     // here the message is hashed according to the sha256 specification
     string hashedMessage = sha256(message);
     cout << "The hash of this message is:" << '\n'
          << '\n'
          << hashedMessage << '\n';

     cout << "----------------------------------------------------------------" << '\n';

     // here we randomly generate a public / private key pair
     ZZ priv, pub, N;
     genKeys(pub, priv, N, 200);

     // here the hashed message is converted into a ZZ value
     ZZ pt;
     pt = ZZFromHex(hashedMessage);

     // this function stores the signed value in variable 'signature'
     ZZ signature;
     sign(signature, pt, priv, N);

     cout << "This hash is signed with the private key to obtain:" << '\n'
          << '\n'
          << toHex(signature) << '\n';

     cout << "----------------------------------------------------------------" << '\n';

     cout << "The public key that can be used for verification is:" << '\n'
          << pub << '\n';

     cout << "----------------------------------------------------------------" << '\n';

     // Verification process
     cout << "This signature can be 'decrypted' using the public key to obtain" << '\n'

          << "the hash of the message. The original message can now be hashed" << '\n'
          << "and this can be compared with the decrypted value from the sign" << '\n'
          << "to verify message authenticity:" << '\n'
          << '\n';
     cout << (verify(message, signature, pub, N) ? "verified!" : "not verified!") << '\n';

     cout << endl;
     return 0;
}