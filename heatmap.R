library(readr)
library(reshape)
library(ggplot2)
library(plotly)

datos <- read_csv("laplace.csv", col_names = "")
datos <- matrix(as.matrix(datos), ncol = 21)
plot_ly(z = datos, type = "heatmap")

# Genera otro tipo de heatmap
# colnames(datos) <- c(rep(0:20))
# rownames(datos) <- c(rep(0:20))
# datos_melt <- melt(datos, varnames = c("fila", "col"))
# heatmap <- ggplot(datos_melt, aes(fila, col))+
#   geom_tile(aes(fill = value))+
#   coord_flip()+
#   theme(axis.title.y=element_blank(), 
#         axis.ticks.y=element_blank(),
#         axis.title.x=element_blank(),
#         axis.ticks.x=element_blank(),
#         axis.text.x=element_blank())
