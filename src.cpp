#include <iostream>
#include <cstring>
#include <cstdlib>
#include <secp256k1.h>
#include <secp256k1_bulletproofs.h>

using namespace std;

int main(int argc, char** argv) {
    // Generate a random 32-byte secret key
    unsigned char sk[32];
    secp256k1_rand256(sk);

    // Generate a random 32-byte value
    unsigned char v[32];
    secp256k1_rand256(v);

    // Generate a Pedersen commitment to the value
    secp256k1_pedersen_commitment comm;
    if (!secp256k1_pedersen_commit(ctx, &comm, sk, v, NULL, NULL)) {
        cerr << "Error: failed to create Pedersen commitment" << endl;
        return 1;
    }

    // Generate a Bulletproof for the commitment
    secp256k1_bulletproof_generators gens;
    secp256k1_bulletproof_generators_init(&gens, 64, 1);
    secp256k1_bulletproof_proof proof;
    unsigned char message[32];
    unsigned char blinding_factor[32];
    memset(message, 0, sizeof(message));
    memset(blinding_factor, 0, sizeof(blinding_factor));
    if (!secp256k1_bulletproof_prove(ctx, &proof, &gens, &comm, NULL, NULL, blinding_factor, v, message, sizeof(message))) {
        cerr << "Error: failed to create Bulletproof" << endl;
        return 1;
    }

    // Verify the Bulletproof
    if (!secp256k1_bulletproof_verify(ctx, &proof, &gens, &comm, NULL, NULL, v, message, sizeof(message))) {
        cerr << "Error: failed to verify Bulletproof" << endl;
        return 1;
    }

    cout << "Bulletproof verified!" << endl;

    return 0;
}
