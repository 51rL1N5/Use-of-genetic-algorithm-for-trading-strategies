# IAPU2

# Authors
- Felipe Oliveira Lins e Silva
- Luís Gabriel Pereira Condados
- Heitor Carlos de Medeiros Dantas
- Rejane Nobre Bezerra

This project consists in an implementation of a Genetic Algorithm to develop a trading strategy. Also, it is a unit 2 project of the course Applied Artificial Inteligence, of Universidade Federal do Rio Grande do Norte (UFRN), taught by Sergio Natan Silva.

It's totally based on Imanol Perez's work (https://github.com/imanolperez/Genetic-algorithm-for-trading-in-cpp). All credits for him due the idea.

His idea consist in use S&P500 data to "train" a population, with the objective to find the best trading strategy. The trading strategy consists in a pair of two integer values, the moving average window size, MA1 and MA2. If MA1 > MA2, buy the S&P500. Otherwise, short the S&P500.

# TO DO
- Check if using Exponential Moving Average we achieve better results
