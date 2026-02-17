package bg.sofia.uni.fmi.mjt.show.elimination;

import bg.sofia.uni.fmi.mjt.show.ergenka.Ergenka;

public class PublicVoteEliminationRule implements EliminationRule {

    private final String[] votes;

    public PublicVoteEliminationRule(String[] votes) {
        this.votes = votes;
    }
    @Override
    public Ergenka[] eliminateErgenkas(Ergenka[] ergenkas) {
        String elem = "";
        int count = 0;
        for (String vote : votes) {
            if (count == 0) {
                elem = vote;
                count = 1;
            }
            else if (vote.equals(elem)) {
                count++;
            }
            else {
                count--;
            }
        }
        count = 0;
        for (String vote : votes) {
            if (vote.equals(elem)) {
                count++;
            }
        }

        if (count > (double)votes.length / 2.0) {
            for (int i = 0; i < ergenkas.length; ++i) {
                if (elem.equals(ergenkas[i].getName())) {
                    for (int j = i; j < ergenkas.length; ++j) {
                        ergenkas[j] = ergenkas[j + 1];
                    }
                    break;
                }
            }

            Ergenka[] leftErgenkas = new Ergenka[ergenkas.length - 1];
            System.arraycopy(ergenkas, 0, leftErgenkas, 0, ergenkas.length - 1);

            return leftErgenkas;
        }

        return ergenkas;
    }
}
