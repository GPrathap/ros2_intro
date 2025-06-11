import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque
import csv
import time
import os

class LatencyLogger(Node):
    def __init__(self, label='ipc_on'):
        super().__init__('latency_logger')
        self.label = label
        self.latencies = deque(maxlen=200)
        self.times = deque(maxlen=200)
        self.start_time = time.time()
        self.csv_file = f"latency_log_{label}.csv"
        self._init_csv()

        self.subscription = self.create_subscription(
            PointCloud2,
            'cloud',
            self.callback,
            10)

    def _init_csv(self):
        if not os.path.exists(self.csv_file):
            with open(self.csv_file, mode='w', newline='') as file:
                writer = csv.writer(file)
                writer.writerow(["elapsed_time_sec", "latency_ms", "label"])

    def callback(self, msg):
        now = self.get_clock().now()
        sent_time = rclpy.time.Time.from_msg(msg.header.stamp)
        latency_ms = (now - sent_time).nanoseconds * 1e-6
        elapsed_time = time.time() - self.start_time

        self.latencies.append(latency_ms)
        self.times.append(elapsed_time)

        with open(self.csv_file, mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([elapsed_time, latency_ms, self.label])

def live_plot(logger: LatencyLogger):
    fig, ax = plt.subplots()
    line, = ax.plot([], [], label=logger.label, lw=2)
    ax.set_title('PointCloud Latency Comparison')
    ax.set_xlabel('Elapsed Time (s)')
    ax.set_ylabel('Latency (ms)')
    ax.grid(True)
    ax.legend(loc='upper right')

    def init():
        line.set_data([], [])
        return line,

    def update(frame):
        line.set_data(logger.times, logger.latencies)
        ax.relim()
        ax.autoscale_view()
        return line,

    ani = animation.FuncAnimation(fig, update, init_func=init, blit=True, interval=100)
    plt.show()

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--label', type=str, default='ipc_on', help='Label for this run (e.g., ipc_on or ipc_off)')
    args = parser.parse_args()

    rclpy.init()
    node = LatencyLogger(label=args.label)

    try:
        import threading
        t = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
        t.start()
        live_plot(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
