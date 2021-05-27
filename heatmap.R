library(readr)
library(plotly)

datos <- read_csv("laplace.csv", col_names = "")
datos <- matrix(as.matrix(datos), ncol = sqrt(nrow(datos)))
plot_ly(z = datos, type = "heatmap")
