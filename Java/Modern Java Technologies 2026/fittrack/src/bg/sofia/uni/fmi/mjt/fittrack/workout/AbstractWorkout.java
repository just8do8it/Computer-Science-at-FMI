package bg.sofia.uni.fmi.mjt.fittrack.workout;

public abstract non-sealed class AbstractWorkout implements Workout {
    private final String name;
    private final int duration;
    private final int caloriesBurned;
    private final int difficulty;

    AbstractWorkout(String name, int duration, int caloriesBurned, int difficulty) {
        this.name = name;
        this.duration = duration;
        this.caloriesBurned = caloriesBurned;
        this.difficulty = difficulty;
    }
    protected boolean validateData(String name, int duration, int caloriesBurned, int difficulty) {
        return name != null && !name.isBlank() &&
                caloriesBurned > 0 &&
                difficulty >= 1 && difficulty <= 5;
    }
    @Override
    public String getName() {
        return name;
    }

    @Override
    public int getDuration() {
        return duration;
    }

    @Override
    public int getCaloriesBurned() {
        return caloriesBurned;
    }

    @Override
    public int getDifficulty() {
        return difficulty;
    }

    @Override
    public String toString() {
        return this.getType() + "[name='" + name + "', duration=" + duration + ", calories=" + caloriesBurned + ", difficulty=" + difficulty + "]";
    }
}
