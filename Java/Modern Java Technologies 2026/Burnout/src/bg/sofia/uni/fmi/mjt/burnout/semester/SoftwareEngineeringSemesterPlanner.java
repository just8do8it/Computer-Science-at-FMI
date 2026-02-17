package bg.sofia.uni.fmi.mjt.burnout.semester;

import bg.sofia.uni.fmi.mjt.burnout.exception.CryToStudentsDepartmentException;
import bg.sofia.uni.fmi.mjt.burnout.exception.InvalidSubjectRequirementsException;
import bg.sofia.uni.fmi.mjt.burnout.plan.SemesterPlan;
import bg.sofia.uni.fmi.mjt.burnout.subject.SubjectRequirement;
import bg.sofia.uni.fmi.mjt.burnout.subject.UniversitySubject;

public non-sealed class SoftwareEngineeringSemesterPlanner implements SemesterPlannerAPI {
    @Override
    public UniversitySubject[] calculateSubjectList(SemesterPlan semesterPlan) throws InvalidSubjectRequirementsException {
        // Implements the method by minimizing the number
        // of subjects that cover the credits requirements.

        CalcSubjectsCheckForExceptions(semesterPlan);

        int n = semesterPlan.subjects().length;

        // Compute max possible credits to bound DP
        int S = 0;
        for (UniversitySubject s : semesterPlan.subjects()) {
            S += s.credits();
        }

        int INF = 1_000_000_000;

        // dp[s] = minimum number of subjects to get exactly s credits
        int[] dp = new int[S + 1];
        for (int i = 1; i < S + 1; ++i) {
            dp[i] = INF;
        }
        dp[0] = 0;

        // parent[s] = index of subject used last to form sum s, or -1
        // prevSum[s] = previous sum before adding subject parent[s]
        int[] parent = new int[S + 1];
        int[] prevSum = new int[S + 1];
        for (int i = 1; i < S + 1; ++i) {
            parent[i] = -1;
            prevSum[i] = -1;
        }

        for (int i = 0; i < n; i++) {
            int c = semesterPlan.subjects()[i].credits();
            // iterate sums backwards to avoid reusing the same subject multiple times
            for (int s = S; s >= c; s--) {
                if (dp[s - c] + 1 < dp[s]) {
                    dp[s] = dp[s - c] + 1;
                    parent[s] = i;
                    prevSum[s] = s - c;
                }
            }
        }

        // find the smallest sum >= requiredCredits that is reachable
        int bestSum = -1;
        int bestCount = INF;
        for (int s = semesterPlan.minimalAmountOfCredits(); s <= S; s++) {
            if (dp[s] < bestCount) {
                bestCount = dp[s];
                bestSum = s;
            }
        }

        if (bestSum == -1 || bestCount == INF) {
            // No way to reach requiredCredits
            return new UniversitySubject[0];
        }

        // Reconstruct chosen subjects
        UniversitySubject[] chosen = new UniversitySubject[n];
        int counter = 0;
        int cur = bestSum;
        while (cur > 0) {
            int idx = parent[cur];
            if (idx == -1) break; // safety
            chosen[counter] = semesterPlan.subjects()[idx];
            counter++;
            cur = prevSum[cur];
        }

        return chosen;
    }
}