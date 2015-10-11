public class KeyPair {
	private Key privateKey;
	private Key publicKey;
	
	public KeyPair() {
		this(Algorithms.getRandomPrime(), Algorithms.getRandomPrime());
	}
	public KeyPair(int p, int q) {
		double n = p * q;
		double totient = Algorithms.getTotient(p, q);
		publicKey = Key.generatePublicKey(n,totient);
		privateKey = Key.generatePrivateKey(n, publicKey.getDE(),totient);
	}
	
	public KeyPair(Key privateKey, Key publicKey) {
		this.privateKey = privateKey;
		this.publicKey = publicKey;
	}
	
	public String toString() {
		return	"Private key: n = " + privateKey.getN() + ", " + "d = " + privateKey.getDE() + "\n" +
				"Public key: n = " + publicKey.getN() + ", " + "e = " + publicKey.getDE();		
	}
	
	public Key getPrivateKey() { return privateKey; }
	public Key getPublicKey() { return publicKey; }
}