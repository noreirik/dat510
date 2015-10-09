public class KeyPair {
	private Key privateKey;
	private Key publicKey;
	
	public KeyPair() {
		int p = Algorithms.getRandomPrime();
		int q = Algorithms.getRandomPrime();
		double n = p * q;
		double totient = Algorithms.getTotient(p, q);
		publicKey = Key.generatePublicKey(n,totient);
		privateKey = Key.generatePrivateKey(n, publicKey.getDE(),totient);
	}
	
	public KeyPair(Key privateKey, Key publicKey) {
		this.privateKey = privateKey;
		this.publicKey = publicKey;
	}
	
	public Key getPrivateKey() { return privateKey; }
	public Key getPublicKey() { return publicKey; }
}