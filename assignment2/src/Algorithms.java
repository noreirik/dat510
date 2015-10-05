public class Algorithms {
	
	/*
	 * Using Euclid's algorithm, return the great common divisor of a and b
	 */
	public static int gcd(int a, int b) {
		if (b == 0) return a;
		else return gcd(b, a % b);
	}
	
}
