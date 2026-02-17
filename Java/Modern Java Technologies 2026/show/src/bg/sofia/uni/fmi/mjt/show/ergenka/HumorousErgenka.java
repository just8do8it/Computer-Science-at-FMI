package bg.sofia.uni.fmi.mjt.show.ergenka;

import bg.sofia.uni.fmi.mjt.show.date.DateEvent;
import java.lang.String;
public class HumorousErgenka implements Ergenka {

    private final String name;
    private final short age;
    private final int romanceLevel;
    private final int humorLevel;
    private int rating;
    private final String favoriteDateLocation;

    public HumorousErgenka(String name, short age, int romanceLevel, int humorLevel, int rating, String favoriteDateLocation){
        this.name = name;
        this.age = age;
        this.romanceLevel = romanceLevel;
        this.humorLevel = humorLevel;
        this.rating = rating;
        this.favoriteDateLocation = favoriteDateLocation;
    }
    @Override
    public String getName() {
        return name;
    }

    @Override
    public short getAge() {
        return age;
    }

    @Override
    public int getRomanceLevel() {
        return romanceLevel;
    }

    @Override
    public int getHumorLevel() {
        return humorLevel;
    }

    @Override
    public int getRating() {
        return rating;
    }

    @Override
    public void reactToDate(DateEvent dateEvent) {
        int bonuses = 0;
        bonuses += (dateEvent.getDuration() >= 30 && dateEvent.getDuration() <= 120) ? 4 : 0;
        bonuses += dateEvent.getDuration() < 30 ? -2 : 0;
        bonuses += dateEvent.getDuration() > 120 ? -3 : 0;
        rating = (humorLevel * 5 / dateEvent.getTensionLevel()) + (romanceLevel / 3) + bonuses;
    }
}
