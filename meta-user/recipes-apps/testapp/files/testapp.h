/**
 * @file       testapp.h
 *
 * @brief      Header file of Interface testing
 *
 * @Version   1.0
 *
 * @Author    Capgemini Engineering
 */
#define PING_SUCCESS 0
#define EXIT         3
enum event
{
        SDF_FPGA_PS = 1,
        SDF_FPGA_PL = 2,
        DMB_FPGA_PS = 3,
        DAB_FPGA_PS = 4,
        DAB_FPGA_PL = 5,
        QUIT        = 6
};

enum Testcases
{
        UART_loopback = 1,
        QSPI_Interface_test,
        SPI_Interface_test,
        DDR4_Interface_test,
        I2C_Interface_test,
        RGMII_loopback,
        GMII_loopback,
        SGMII_loopback,
        AFDX_IP_CORE_test,
        PCIe_x2_ROOT_COMPLEXT_test,
        MES_IP_CORE_test,
        Quit,
        Exit
};

