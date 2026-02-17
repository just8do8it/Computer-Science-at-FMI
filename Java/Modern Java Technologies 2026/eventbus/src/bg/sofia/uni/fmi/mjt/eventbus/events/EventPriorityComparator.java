package bg.sofia.uni.fmi.mjt.eventbus.events;

import java.util.Comparator;
import bg.sofia.uni.fmi.mjt.eventbus.events.Event;

public class EventPriorityComparator<T extends Event<?>> implements Comparator<T> {

    @Override
    public int compare(T e1, T e2) {
        int result = Integer.compare(e1.getPriority(), e2.getPriority());
        if (result != 0) {
            return result;
        }

        return e1.getTimestamp().compareTo(e2.getTimestamp());
    }
}
