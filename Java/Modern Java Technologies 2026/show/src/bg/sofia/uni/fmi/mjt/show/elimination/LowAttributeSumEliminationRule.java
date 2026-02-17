package bg.sofia.uni.fmi.mjt.show.elimination;

import bg.sofia.uni.fmi.mjt.show.ergenka.Ergenka;

public class LowAttributeSumEliminationRule implements EliminationRule {

    private final int threshold;

    public LowAttributeSumEliminationRule(int threshold) {
        this.threshold = threshold;
    }
    @Override
    public Ergenka[] eliminateErgenkas(Ergenka[] ergenkas) {
        int numOfEliminated = 0;
        for (int i = 0; i < ergenkas.length; ++i) {
            if (threshold > ergenkas[i].getHumorLevel() + ergenkas[i].getRomanceLevel()) {
                for (int j = i; j < ergenkas.length; ++j) {
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
