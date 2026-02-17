package bg.sofia.uni.fmi.mjt.eventbus.events;

import java.time.Instant;
import java.util.Objects;

public final class SimpleEvent<T extends Payload<?>> implements Event<T> {
    private final Instant timestamp;
    private final int priority;
    private final String source;
    private final T payload;

    public SimpleEvent(
            Instant timestamp,
            int priority,
            String source,
            T payload
    ) {
        this.timestamp = timestamp;
        this.priority = priority;
        this.source = source;
        this.payload = payload;
    }

    public Instant timestamp() {
        return timestamp;
    }

    public int priority() {
        return priority;
    }

    public String source() {
        return source;
    }

    public T payload() {
        return payload;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null || obj.getClass() != this.getClass()) return false;
        var that = (SimpleEvent) obj;
        return Objects.equals(this.timestamp, that.timestamp) &&
                this.priority == that.priority &&
                Objects.equals(this.source, that.source) &&
                Objects.equals(this.payload, that.payload);
    }

    @Override
    public int hashCode() {
        return Objects.hash(timestamp, priority, source, payload);
    }

    @Override
    public String toString() {
        return "SimpleEvent[" +
                "timestamp=" + timestamp + ", " +
                "priority=" + priority + ", " +
                "source=" + source + ", " +
                "payload=" + payload + ']';
    }

    @Override
    public Instant getTimestamp() {
        return timestamp;
    }

    @Override
    public int getPriority() {
        return priority;
    }

    @Override
    public String getSource() {
        return source;
    }

    @Override
    public T getPayload() {
        return payload;
    }
}