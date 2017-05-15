#METODO=gauss
DIM_MINIMA=100
DIM_MAXIMA=100
DIM_STEP=20
CANT_POR_DIM=5
CANT_VEC_B=20
PATH_SALIDA=.

for ((i=1; i <= $CANT_VEC_B; i++)); do
    for METODO_NUM in 0 1; do

        if [ $METODO_NUM -eq "0" ]; then
            METODO=gauss
        fi

        if [ $METODO_NUM -eq "1" ]; then
            METODO=cholesky
        fi

        SALIDA_NOMBRE=$METODO\_dmin$DIM_MINIMA\_dmax$DIM_MAXIMA\_step$DIM_STEP\_dcant$CANT_POR_DIM\_bcant$i
        echo $SALIDA_NOMBRE

        ./benchmark $PATH_SALIDA $SALIDA_NOMBRE $METODO_NUM $DIM_MINIMA $DIM_MAXIMA $DIM_STEP $CANT_POR_DIM $i

        if [ $DIM_MINIMA -eq $DIM_MAXIMA ]; then
            SALIDA_VARIANDO_CANT_B=$METODO\_dmin$DIM_MINIMA\_dcant$CANT_POR_DIM\_bcant$CANT_VEC_B
            if [ -e $SALIDA_VARIANDO_CANT_B ]; then 
                echo -e >> $SALIDA_VARIANDO_CANT_B 
            fi
            cat $SALIDA_NOMBRE >> $SALIDA_VARIANDO_CANT_B
        fi
    done
done