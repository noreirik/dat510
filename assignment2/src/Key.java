public abstract class Key {
	private double n;
	private int de;
	
	public Key() {
		this.generateKey();
	}
	protected abstract void generateKey();
}
