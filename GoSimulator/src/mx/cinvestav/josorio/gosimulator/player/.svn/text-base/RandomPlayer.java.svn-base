package mx.cinvestav.josorio.gosimulator.player;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import mx.cinvestav.josorio.gosimulator.Analyzer;
import mx.cinvestav.josorio.gosimulator.Pair;
import mx.cinvestav.josorio.gosimulator.player.Player;
import mx.cinvestav.josorio.gosimulator.player.PlayerType;

/**
 * Simulates a random player avoiding suicide.
 * @author Moises Osorio
 */
public class RandomPlayer extends Player {

	private Random random;
	
	public RandomPlayer() {
		random = new Random();
	}
	
	@Override
	protected Pair doMakeTurn(Analyzer analysis) {
		List<Integer> options = new ArrayList<Integer>();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (analysis.getBoard()[i][j] == PlayerType.EMPTY) {
					if (analysis.isSuicide(i, j))
						continue;
					
					options.add(i);
					options.add(j);
				}
		
		int x = -1;
		int y = -1;
		if (!options.isEmpty()) {
			int choice = random.nextInt(options.size() / 2);
			x = options.get(choice*2);
			y = options.get(choice*2 + 1);
		}
		
		return new Pair(x, y);
	}
	
}
