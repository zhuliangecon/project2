# Install and load required packages

library(ggplot2)
library(gridExtra)

# Updated data
data_updated <- data.frame(
  P = c(4, 4, 4, 4, 7, 7, 7, 7, 28, 28, 28, 28, 37, 37, 37, 37),
  N = c(2^10, 2^12, 2^14, 2^16, 2^10, 2^12, 2^14, 2^16, 2^10, 2^12, 2^14, 2^16, 2^10, 2^12, 2^14, 2^16),
  MPI_Bcast = c(0.000008, 0.000011, 0.000031, 0.000099, 0.000011, 0.000020, 0.000048, 0.000156, 
                0.000022, 0.000035, 0.000100, 0.000349, 0.000026, 0.000045, 0.000143, 0.000564),
  MY_Bcast = c(0.000007, 0.000010, 0.000022, 0.000065, 0.000015, 0.000026, 0.000064, 0.000212, 
               0.000031, 0.000053, 0.000152, 0.000477, 0.000035, 0.000063, 0.000178, 0.000616)
)

# Determine the y-axis limits based on the maximum time from both MPI_Bcast and MY_Bcast
y_max <- max(c(data_updated$MPI_Bcast, data_updated$MY_Bcast))

# Plot for MPI_Bcast with fixed y-axis
plot_MPI_fixed <- ggplot(data_updated, aes(x=P, y=MPI_Bcast, group=N, color=as.factor(N))) +
  geom_line() +
  geom_point() +
  labs(title="Performance of MPI_Bcast", x="No. of Processes (P)", y="Time (sec)", color="N") +
  scale_color_discrete(name="N value", labels=sapply(unique(data_updated$N), format_label)) +
  ylim(0, y_max)  # Set y-axis limits

# Plot for MY_Bcast with fixed y-axis
plot_MY_fixed <- ggplot(data_updated, aes(x=P, y=MY_Bcast, group=N, color=as.factor(N))) +
  geom_line() +
  geom_point() +
  labs(title="Performance of MY_Bcast", x="No. of Processes (P)", y="Time (sec)", color="N") +
  scale_color_discrete(name="N value", labels=sapply(unique(data_updated$N), format_label)) +
  ylim(0, y_max)  # Set y-axis limits

# Arrange the plots with fixed y-axis side by side
grid.arrange(plot_MPI_fixed, plot_MY_fixed, ncol=2)


