import java.util.Random;

public class Algorithms {
	
	/*
	 * Using Euclid's algorithm, return the great common divisor of a and b
	 */
	public static double gcd(double a, double b) {
		if (b == 0) return a;
		else if (b == 1) return 1;
		else return gcd(b, a % b);
	}
	
	/*
	 * return true if the two numbers are relative prime, i.e
	 * that their great common divisor is 1 
	 */
	public static boolean isRelativePrime (double a, double b) {
		return gcd(a, b) == 1;
	}
	
	/*
	 * Return the result of the Euler totient function for
	 * two prime numbers p and q
	 */
	public static double getTotient(int p, int q) {
		return (p - 1)*(q - 1);
	}
	
	/*
	 * Return a randomly generated prime number
	 */
	public static int getPrime() {
		Random rand = new Random();
		while (true) {
			int p = rand.nextInt();
			if (isPrime(p)) return p;
		}
	}
	
	/*
	 * TODO: Using some algorithm, determine if a is a prime number
	 */
	public static boolean isPrime(int a) {
		return true;
	}

}
