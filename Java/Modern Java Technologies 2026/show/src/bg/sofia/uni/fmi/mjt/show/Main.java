package bg.sofia.uni.fmi.mjt.show;

import bg.sofia.uni.fmi.mjt.show.date.DateEvent;
import bg.sofia.uni.fmi.mjt.show.elimination.EliminationRule;
import bg.sofia.uni.fmi.mjt.show.elimination.LowAttributeSumEliminationRule;
import bg.sofia.uni.fmi.mjt.show.elimination.LowestRatingEliminationRule;
import bg.sofia.uni.fmi.mjt.show.elimination.PublicVoteEliminationRule;
import bg.sofia.uni.fmi.mjt.show.ergenka.Ergenka;
import bg.sofia.uni.fmi.mjt.show.ergenka.HumorousErgenka;
import bg.sofia.uni.fmi.mjt.show.ergenka.RomanticErgenka;
import java.lang.System;

public class Main {
    public static void main(String[] args) {
        Ergenka teodora = new HumorousErgenka("Teodora", (short) 23, 50, 25, 8, "Nedelya");
        Ergenka monika = new RomanticErgenka("Monika", (short) 28, 40, 45, 7, "Dom na kinoto");
        Ergenka elena = new HumorousErgenka("Elena", (short) 27, 45, 30, 9, "Park Borisova gradina");
        Ergenka desislava = new RomanticErgenka("Desislava", (short) 25, 55, 20, 8, "Ndk");
        Ergenka katya = new HumorousErgenka("Katya", (short) 29, 42, 48, 6, "Zaimov park");
        Ergenka iveta = new RomanticErgenka("Iveta", (short) 24, 60, 35, 7, "Vitosha bul.");
        Ergenka simona = new HumorousErgenka("Simona", (short) 26, 38, 27, 9, "Orlov most");
        Ergenka aneliya = new RomanticErgenka("Aneliya", (short) 30, 50, 40, 8, "Mladost 1A");
        Ergenka veronika = new HumorousErgenka("Veronika", (short) 22, 35, 29, 7, "Studentski grad");
        Ergenka petya = new RomanticErgenka("Petya", (short) 28, 52, 33, 8, "Lozenets");
        Ergenka venera = new HumorousErgenka("Venera", (short) 25, 47, 44, 6, "Loven park");
        Ergenka borislava = new RomanticErgenka("Borislava", (short) 31, 41, 21, 9, "Serdika Center");
        Ergenka yordanka = new HumorousErgenka("Yordanka", (short) 23, 50, 38, 8, "Mall Sofia");
        Ergenka denitsa = new RomanticErgenka("Denitsa", (short) 27, 44, 46, 7, "Largo");
        Ergenka tanq = new HumorousErgenka("Tanq", (short) 29, 37, 39, 9, "Ovcha kupel");
        Ergenka kalina = new RomanticErgenka("Kalina", (short) 24, 57, 24, 8, "The Mall");
        Ergenka stela = new HumorousErgenka("Stela", (short) 26, 49, 32, 9, "Doktorska gradina");
        Ergenka margarita = new RomanticErgenka("Margarita", (short) 28, 53, 44, 7, "Aleksandur Nevski");
        Ergenka nadezhda = new HumorousErgenka("Nadezhda", (short) 25, 46, 25, 6, "Dragalevtsi");
        Ergenka kristina = new RomanticErgenka("Kristina", (short) 27, 59, 28, 8, "Borisova gradina");
        Ergenka lubomira = new HumorousErgenka("Lubomira", (short) 30, 43, 36, 9, "Muzeika");
        Ergenka silviya = new RomanticErgenka("Silviya", (short) 23, 51, 31, 7, "Zaimov park");

        Ergenka[] ergenkas = {teodora, monika, elena, desislava, katya, iveta, simona, aneliya, veronika, petya,
        venera, borislava, yordanka, denitsa, tanq, kalina, stela, margarita, nadezhda, kristina, lubomira, silviya};

        String[] ergenkaVotes = {
                "Elena", "Elena", "Elena", "Elena", "Elena", "Elena", "Elena", "Elena", "Elena", "Elena", "Elena",
                "Monika", "Teodora", "Iveta", "Simona", "Katya", "Aneliya", "Desislava", "Veronika", "Anelya", "Elena"
        };

        EliminationRule[] rules = {
                new LowestRatingEliminationRule(),
                new LowAttributeSumEliminationRule(80),
                new PublicVoteEliminationRule(ergenkaVotes)
        };

        ShowAPIImpl api = new ShowAPIImpl(ergenkas, rules);
        DateEvent dateEvent = new DateEvent("Sv. Nedelya", 54, 90);
        api.playRound(dateEvent);
        api.eliminateErgenkas(rules);

        for (Ergenka ergenka : api.getErgenkas()) {
            System.out.println(ergenka.getName());
        }
    }
}