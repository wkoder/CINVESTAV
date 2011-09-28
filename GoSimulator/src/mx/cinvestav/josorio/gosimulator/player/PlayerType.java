package mx.cinvestav.josorio.gosimulator.player;

/**
 * Board square states.
 * @author Moises Osorio
 */
public enum PlayerType {

	BLACK,
	WHITE,
	EMPTY;
	
	public String toString() {
		return super.toString().charAt(0) + "";
	}
}
