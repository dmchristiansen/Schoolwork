# Daniel Christiansen
# CS 445
# HW 6 - Reinforcement Learning

# Experiment 5, part 2
# Increased sensor range

# Steps for training:
# Observe Robby’s current state st
# Choose an action a_t, using epsilon-greedy action selection
# Perform the action
# Receive reward r_t (which is zero except in the cases specified above)
# Observe Robby’s new state s_t+1
# Update Q(s_t, a_t) = Q(s_t, a_t) + eta(r_t + gamma * max(Q(s_t+1, a')) - Q(s_t, a_t))

import numpy as np
import matplotlib.pyplot as mpl
np.set_printoptions(threshold=np.inf)

# Hyperparameters
N = 5000        # number of episodes
M = 200         # number of steps per episode
epsilon = 1     # chance to choose a random action
eta = 0.2       # learning rate
gamma = 0.9     # scaling factor for value of future actions

class Robot:

    def __init__(self):
        self.x = 1
        self.y = 1
        self.epsilon = 1

        # 10 x 10 + edges made of walls
        self.grid = np.zeros((12, 12))

        """
        Q-matrix
        Rows are states (sensor values interpreted as base-3)
        Columns are actions: [Up, Down, Right, Left, Pick up can]
        Entries are expected [(state x action) -> reward] values
        """
        self.Q = np.zeros((1594323, 5))

        """
        81, 27, 9, 3, 1
         N,  S, E, W, H
        Grid states: Empty = 0, Can = 1, Wall = 2
        """
        self.state = 0
        self.state = self.read_sensor()

    def test(self):
        """
        Tests robot over N episodes
        """
        global epsilon
        test_reward  = []

        for i in range(int(N/50)):
            for j in range(50):
                test_reward.append(self.episode())

        print("test average reward: " + str(np.mean(test_reward)))
        print("test standard deviation: " + str(np.std(test_reward)))


    def train(self):
        """
        Trains robot over N episodes
        """
        global epsilon
        training_reward = []

        for i in range(int(N/50)):
            for j in range(50):
                training_reward.append(self.episode(train=True))
            # Adjust epsilon throughout training
            if epsilon > 0.1:
                epsilon -= 0.01

        # Plot training data
        plot_data = []
        plot_points = list(range(0, N, 100))
        for i in plot_points:
            plot_data.append(training_reward[i])

        mpl.figure()
        mpl.plot(plot_points, plot_data)
        mpl.title("Training Rewards (every 100th episode)")
        mpl.xlabel("episode")
        mpl.ylabel("total reward")
        mpl.savefig("training reward action tax " + str(epsilon) + ".png")

    def episode(self, train=False):
        """
        Goes through one episode of M steps
        """
        robby.reset_grid()
        robby.read_sensor()

        episode_reward = 0

        for i in range(M):
            episode_reward += robby.step(train=train)

        return episode_reward

    def step(self, train=False):
        """
        Goes through the steps of a single step of sense -> act -> reward -> sense -> update Q
        """

        action = robby.choose_action()
        reward = robby.take_action(action)
        robby.read_sensor()
        if train == True:
            robby.update_q(reward, action)
        return reward

    def update_q(self, reward, action):
        # Update Q(s_t, a_t) = Q(s_t, a_t) + eta(r_t + gamma * max(Q(s_t+1, a')) - Q(s_t, a_t))
        self.Q[self.previous_state, action] = self.Q[self.previous_state, action] + \
                                              eta * (reward + gamma * (np.amax(self.Q[self.state])) -
                                                     self.Q[self.previous_state, action])

    def take_action(self, action):
        """
        Takes indicated action and returns appropriate reward value
        """

        # Go North
        if action == 0:
            x = self.x
            y = self.y - 1

        # Go South
        if action == 1:
            x = self.x
            y = self.y + 1

        # Go East
        if action == 2:
            x = self.x + 1
            y = self.y

        # Go West
        if action == 3:
            x = self.x - 1
            y = self.y

        # Pick up can
        if action == 4:
            # If there's a can in the space, remove it and give reward
            if self.grid[self.y, self.x] == 1:
                self.grid[self.y, self.x] = 0
                return 10
            # If not, return penalty
            else:
                return -1

        # Make sure there's not a wall in the way.  If so, bounce back, return penalty.
        if self.grid[y, x] == 2:
            return -5
        # If not, update position and return reward/penalty associated with movement
        else:
            self.x = x
            self.y = y
            return 0

    def choose_action(self):
        """
        Epsilon-greedy action selection
        """

        if np.random.uniform() > epsilon:
            # Choose best action
            return np.argmax(self.Q[self.state])
        else:
            # Choose random action
            return np.random.randint(5)

    def read_sensor(self):
        """
        Fills 'sensor' array with grid information based on x, y coordinates
        Assumes that robot isn't in a 'wall' location
        sensor is filled in the following manner:
         X  X  2  X  X
         X 12  1  3  X
        11 10  0  4  5
         X  9  7  6  X
         X  X  8  X  X
        """
        sensor = np.zeros(13, dtype=np.int)
        sensor[0] = self.grid[self.y, self.x]
        sensor[1] = self.grid[self.y - 1, self.x]
        sensor[2] = self.grid[self.y - 2, self.x]
        sensor[3] = self.grid[self.y - 1, self.x + 1]
        sensor[4] = self.grid[self.y, self.x + 1]
        sensor[5] = self.grid[self.y, self.x + 2]
        sensor[6] = self.grid[self.y + 1, self.x + 1]
        sensor[7] = self.grid[self.y + 1, self.x]
        sensor[8] = self.grid[self.y + 2, self.x]
        sensor[9] = self.grid[self.y + 1, self.x - 1]
        sensor[10] = self.grid[self.y, self.x - 1]
        sensor[11] = self.grid[self.y, self.x - 2]
        sensor[12] = self.grid[self.y - 1, self.x - 1]


        # Updates and returns sensor values interpreted as a base-3 value.
        self.previous_state = self.state
        self.state = np.dot(sensor, [531441, 177147, 59049, 19683, 6561, 2187, 729, 243, 81, 27, 9, 3, 1])
        return sensor

    def reset_grid(self):
        """
        Set grid to empty(0), set edges to walls (2), and randomly place cans (1)
        Randomly place robot
        """
        self.x = np.random.randint(2, 12)
        self.y = np.random.randint(2, 12)

        self.grid = np.random.randint(2, size=(14,14))
        self.grid[0].fill(2)
        self.grid[1].fill(2)
        self.grid[12].fill(2)
        self.grid[13].fill(2)
        self.grid[:, 0].fill(2)
        self.grid[:, 1].fill(2)
        self.grid[:, 12].fill(2)
        self.grid[:, 13].fill(2)


if __name__ == "__main__":

    robby = Robot()
    robby.train()
    robby.test()