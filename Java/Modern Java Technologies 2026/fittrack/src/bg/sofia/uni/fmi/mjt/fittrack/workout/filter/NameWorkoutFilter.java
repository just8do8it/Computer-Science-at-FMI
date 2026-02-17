package bg.sofia.uni.fmi.mjt.fittrack.workout.filter;

import bg.sofia.uni.fmi.mjt.fittrack.workout.Workout;

import java.util.Locale;

public class NameWorkoutFilter implements WorkoutFilter {
    private final String keyword;
    private final boolean caseSensitive;

    public NameWorkoutFilter(String keyword, boolean caseSensitive) {
        this.keyword = keyword;
        this.caseSensitive = caseSensitive;

        if (keyword.isBlank() || keyword.isEmpty()) {
            throw new IllegalArgumentException();
        }
    }

    @Override
    public boolean matches(Workout workout) {
        String workoutName = workout.getName();
        if (!caseSensitive) {
            workoutName = workoutName.toLowerCase(Locale.ROOT);
        }

        return (workoutName.contains(keyword) ||
            keyword.contains(workoutName));
    }
}
