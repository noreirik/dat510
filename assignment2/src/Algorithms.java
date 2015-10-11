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
	public static int getRandomNumber(int min, int max) { return min+getRandomNumber(max-min); }
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
	public static double modInverse(double a, double b) {
		double b0 = b; double t, q;
		double x0 = 0, x1 = 1;
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
	 * return a^b (mod m)
	 */
	public static double modExp(double a, int b, double m) {
		double c = 0, f = 1;
		for (int i = getBitCount(b); i >= 0; i--) {
			c *= 2;
			f = (f * f) % m;
			if (isBitSet(b,i)) {
				c++;
				f = (f * a) % m;
			}
		}
		return f;
	}

	// Check if bit index in a is set
	public static boolean isBitSet(int a, int index) { return ((a >> index) & 1) == 1;	}
	// Determine bit position of highest 1
	public static int getHighestBitPosition(int i) {
		int j = 0;
		while (i != 0) {
			i /= 2;
			if (i != 0) j++;
		}
		return j;
	}
	// If a number is represented as the binary stream b[k],b[k-1],...,b[1],b[0], return k
	public static int getBitCount(int i) { return getHighestBitPosition(Integer.highestOneBit(i)); }
	
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
