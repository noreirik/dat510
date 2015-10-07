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
	public static boolean isRelativePrime (double a, double b) { return gcd(a, b) == 1; }
	
	/*
	 * Return the result of the Euler totient function for
	 * two prime numbers p and q
	 */
	public static double getTotient(int p, int q) { return (p - 1)*(q - 1); }
	
	/*
	 * Generate a pseudo-random number
	 */
	public static int getRandomNumber() { return getRandomNumber(Integer.MAX_VALUE); }
	public static int getRandomNumber(int max) { return new Random().nextInt(max); }
	
	/*
	 * Return a randomly generated prime number
	 */
	public static int getRandomPrime() {
		while (true) {
			int p = getRandomNumber();
			if (isPrime(p)) return p;
		}
	}

	/*
	 * Implementation of inverse mod based on Extended Euclidean algorithm. Code translated from C++
	 * to Java from http://rosettacode.org/wiki/Modular_inverse#C.2B.2B
	 */
	public static int modInverse(int a, int b) {
		int b0 = b, t, q;
		int x0 = 0, x1 = 1;
		if (b == 1) return 1;
		while (a > 1) {
			q = a / b;
			t = b;
			b = a % b;
			a = t;
			t = x0; x0 = x1 - q * x0;
			x1 = t;
		}
		if (x1 < 0) x1 += b0;
		return x1;
	}
	
	/*
	 * return a^b (mod c)
	 */
	public static int modExp(int a, int b, int c) {
		int r, x = 1;
		
		while (b != 0) {
			r = b % 2;
			b /= 2;
			
			if (r == 1) x = (x * a) % c;
			a = (a * a) % c;
		}
		return x;
	}
	
	/*
	 * TODO: Using Miller-Rabbit algorithm, determine if input is a prime number
	 * A return value of true means that n might be a prime, while a return value of false
	 * means that n is definitely not prime.
	 */
	public static boolean isPrime(int n) {
		// 0, 1 are not prime. 2 is prime; other even numbers are not prime
		if (n == 0 || n == 1) return false;
		if (n == 2) return true;
		if (n % 2 == 0) return false;
		return true;
	}
	
}
