# Bulletproofs-libsecp256k1

This example generates a random 32-byte secret key and a random 32-byte value, and then creates a Pedersen commitment to the value using the secp256k1 library. It then generates a Bulletproof for the commitment using the secp256k1_bulletproofs library, and verifies the proof using the same library.

Note that this is a simplified example and does not include error checking or handling of all possible edge cases. It is also important to use secure random number generation when generating secret keys and other sensitive data.
