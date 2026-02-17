package bg.sofia.uni.fmi.mjt.show.elimination;

import bg.sofia.uni.fmi.mjt.show.ergenka.Ergenka;

public class LowestRatingEliminationRule implements EliminationRule {

    public LowestRatingEliminationRule() {}
    @Override
    public Ergenka[] eliminateErgenkas(Ergenka[] ergenkas) {
        int lowestRating = Integer.MAX_VALUE;
        for (Ergenka ergenka : ergenkas) {
            if (lowestRating > ergenka.getRating()) {
                lowestRating = ergenka.getRating();
            }
        }

        int numOfEliminated = 0;
        for (int i = 0; i < ergenkas.length; ++i) {
            if (lowestRating == ergenkas[i].getRating()) {
                for (int j = i; j < ergenkas.length - 1; ++j) {
                    ergenkas[j] = ergenkas[j + 1];
                }
                numOfEliminated++;
            }
        }

        Ergenka[] leftErgenkas = new Ergenka[ergenkas.length - numOfEliminated];
        System.arraycopy(ergenkas, 0, leftErgenkas, 0, ergenkas.length - numOfEliminated);

        return leftErgenkas;
    }
}
