package bg.sofia.uni.fmi.mjt.fittrack;

import bg.sofia.uni.fmi.mjt.fittrack.exception.OptimalPlanImpossibleException;
import bg.sofia.uni.fmi.mjt.fittrack.workout.Workout;
import bg.sofia.uni.fmi.mjt.fittrack.workout.WorkoutType;
import bg.sofia.uni.fmi.mjt.fittrack.workout.filter.WorkoutFilter;

import java.util.*;

public class FitPlanner implements FitPlannerAPI {
    private final Collection<Workout> workouts;

    public FitPlanner(Collection<Workout> availableWorkouts) {
        this.workouts = availableWorkouts;

        if (availableWorkouts == null) {
            throw new IllegalArgumentException();
        }
    }
    @Override
    public List<Workout> findWorkoutsByFilters(List<WorkoutFilter> filters) {
        if (workouts.isEmpty()) {
            return List.of();
        }

        List<Workout> filteredWorkouts = List.copyOf(workouts);

        Iterator<Workout> iterator = filteredWorkouts.iterator();
        while (iterator.hasNext()) {
            for (WorkoutFilter filter : filters) {
                if (!filter.matches(iterator.next())) {
                    iterator.remove();
                }
            }
        }

        return filteredWorkouts;
    }

    @Override
    public List<Workout> generateOptimalWeeklyPlan(int totalMinutes) throws OptimalPlanImpossibleException {
        if (totalMinutes < 0) {
            throw new IllegalArgumentException();
        }
        if (totalMinutes == 0 || workouts.isEmpty()) {
            return List.of();
        }

        int n = workouts.size();

        // DP table: dp[i][w] = max calories using first i workouts with capacity w
        int[][] dp = new int[n + 1][totalMinutes + 1];

        // Fill the DP table
        Iterator<Workout> iter = workouts.iterator();
        for (int i = 1; i <= n && iter.hasNext(); i++) {
            Workout current = iter.next();
            int duration = current.getDuration();
            int calories = current.getCaloriesBurned();

            for (int w = 0; w <= totalMinutes; w++) {
                // Option 1: don't include this workout
                dp[i][w] = dp[i - 1][w];

                // Option 2: include this workout (if it fits)
                if (duration <= w) {
                    dp[i][w] = Math.max(dp[i][w], dp[i - 1][w - duration] + calories);
                }
            }
        }

        // Backtrack to find which workouts were selected
        List<Workout> selected = new ArrayList<>();
        int w = totalMinutes;

        List<Workout> copy = new ArrayList<>(List.copyOf(workouts));
        copy = copy.reversed();
        iter = copy.iterator();
        for (int i = n; i > 0 && iter.hasNext(); i--) {
            // If value changed, we included this workout
            if (dp[i][w] != dp[i - 1][w]) {
                Workout chosen = iter.next();
                selected.add(chosen);
                w -= chosen.getDuration();
            }
        }

        return selected;
    }

    @Override
    public Map<WorkoutType, List<Workout>> getWorkoutsGroupedByType() {
        if (workouts.isEmpty()) {
            return Map.of();
        }

        Map<WorkoutType, List<Workout>> map = Map.of(
                WorkoutType.CARDIO, new ArrayList<>(),
                WorkoutType.STRENGTH, new ArrayList<>(),
                WorkoutType.YOGA, new ArrayList<>()
        );

        for (Workout workout : workouts) {
            map.get(workout.getType()).add(workout);
        }

        return map;
    }

    @Override
    public List<Workout> getWorkoutsSortedByCalories() {
        if (workouts.isEmpty()) {
            return List.of();
        }

        Comparator<Workout> byCalories = (w1, w2) -> Integer.compare(w1.getCaloriesBurned(), w2.getCaloriesBurned());
        List<Workout> sortedWorkouts = new ArrayList<>(List.copyOf(workouts));
        sortedWorkouts.sort(byCalories);

        return List.copyOf(sortedWorkouts);
    }

    @Override
    public List<Workout> getWorkoutsSortedByDifficulty() {
        if (workouts.isEmpty()) {
            return List.of();
        }
        Comparator<Workout> byDifficulty = (w1, w2) -> Integer.compare(w1.getDifficulty(), w2.getDifficulty());
        List<Workout> sortedWorkouts = new ArrayList<>(List.copyOf(workouts));
        sortedWorkouts.sort(byDifficulty);

        return List.copyOf(sortedWorkouts);
    }

    @Override
    public Set<Workout> getUnmodifiableWorkoutSet() {
        if (workouts.isEmpty()) {
            return Set.of();
        }
        return Set.copyOf(workouts);
    }
}
