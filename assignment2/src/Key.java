public class Key {	
	private double n;
	private int de; //d for private key, e for public key
	
	private Key(double n) {
		this.setN(n);
	}
	
	public static Key generatePublicKey(double n, double totient) {
		int e;
		do {
			e = Algorithms.getRandomNumber();
		} while (!Algorithms.isRelativePrime(totient, e));
		return generatePublicKey(n, e, totient);
	}
	// Allow setting all fields manually
	public static Key generatePublicKey(double n, int e, double totient) {
		Key pubKey  = new Key(n);
		pubKey.setDE(e);
		return pubKey;
	}
	public static Key generatePrivateKey(double n, int e, double totient) {
		int inverse_e = (int) Algorithms.modInverse(e, totient);
		return generatePrivateKey(n, inverse_e);
	}
	//Allow setting all fields manually
	public static Key generatePrivateKey(double n, int d) {
		Key privateKey = new Key(n);
		privateKey.setDE(d);
		return privateKey;
	}
	
	public int getDE() { return de; }
	public double getN() { return n; }
	public void setDE(int de) { this.de = de; }
	public void setN(double n) { this.n = n; }
}