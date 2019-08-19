`include "alu_defines.vh"
`include "mips32_opcodes.vh"
module Ejer1(
    input [5:0] opc, //! Opcode
    input [5:0] func, //! Function
    output reg isJmp, //! Jump signal
    output reg isBeq, //! BEQ signal
    output reg isBne, //! BNE signal
    output reg [1:0] rfWriteDataSel, //! Register File Write Data Select
    output reg rfWriteAddrSel, //! Register File Write Address Select
    output reg rfWriteEnable, //! Register Write Enable
    output reg memWrite, //! Memory Write
    output reg memRead, //! Memory Read
    output reg aluSrc, //! ALU source
    output reg[2:0] aluFunc, //! ALU operation
    output reg bitXtend, //! Bit extension, 0 = sign extend, 1 = zero extend
    output reg invOpcode //! Invalid opcode or function
);
  //TODO: Implement control signals for OR, LW and BEQ


always @(opc or func) begin
  invOpcode=1'b0;
  case (opc)
    6'b000000:begin
        case (func)
          `MIPS_ADD:begin
            isJmp=1'b0;
            isBeq=1'b0;
            isBne=1'b0;

            rfWriteDataSel=2'b00;
            rfWriteAddrSel=1'b0;
            rfWriteEnable=1'b1;

            memWrite=1'b0;
            memRead=1'b0;
            aluFunc=`ALU_ADD;
            aluSrc=1'b0;

            bitXtend=1'b0;
          end
          `MIPS_SUB:begin
            isJmp=1'b0;
            isBeq=1'b0;
            isBne=1'b0;

            rfWriteDataSel=2'b00;
            rfWriteAddrSel=1'b0;
            rfWriteEnable=1'b1;

            memWrite=1'b0;
            memRead=1'b0;
            aluFunc=`ALU_SUB;
            aluSrc=1'b0;

            bitXtend=1'b0;
          end
          `MIPS_AND:begin
            isJmp=1'b0;
            isBeq=1'b0;
            isBne=1'b0;

            rfWriteDataSel=2'b00;
            rfWriteAddrSel=1'b0;
            rfWriteEnable=1'b1;

            memWrite=1'b0;
            memRead=1'b0;
            aluFunc=`ALU_AND;
            aluSrc=1'b0;

            bitXtend=1'b0;
          end
          `MIPS_OR:begin
            isJmp=1'b0;
            isBeq=1'b0;
            isBne=1'b0;

            rfWriteDataSel=2'b00;
            rfWriteAddrSel=1'b0;
            rfWriteEnable=1'b1;

            memWrite=1'b0;
            memRead=1'b0;
            aluFunc=`ALU_OR;
            aluSrc=1'b0;

            bitXtend=1'b0;
          end
          `MIPS_SLT:begin
            isJmp=1'b0;
            isBeq=1'b0;
            isBne=1'b0;

            rfWriteDataSel=2'b00;
            rfWriteAddrSel=1'b0;
            rfWriteEnable=1'b1;

            memWrite=1'b0;
            memRead=1'b0;
            aluFunc=`ALU_SLT;
            aluSrc=1'b0;

            bitXtend=1'b0;
          end
          default:
              invOpcode=1'b1;
        
        endcase      
    end 
    `MIPS_LW:begin
        isJmp=1'b0;
        isBeq=1'b0;
        isBne=1'b0;

        rfWriteDataSel=2'b10;
        rfWriteAddrSel=1'b0;
        rfWriteEnable=1'b0;

        memWrite=1'b0;
        memRead=1'b1;
        aluFunc=`ALU_ADD;
        aluSrc=1'b1;

        bitXtend=1'b0;
    end
    `MIPS_SW:begin
      isJmp=1'b0;
      isBeq=1'b0;
      isBne=1'b0;

      rfWriteDataSel=2'b10;
      rfWriteAddrSel=1'b0;
      rfWriteEnable=1'b0;

      memWrite=1'b1;
      memRead=1'b0;
      aluFunc=`ALU_ADD;
      aluSrc=1'b1;

      bitXtend=1'b0;
    end
    `MIPS_JUMP:begin
      isJmp=1'b1;
      isBeq=1'b0;
      isBne=1'b0;

      rfWriteDataSel=2'b00;
      rfWriteAddrSel=1'b0;
      rfWriteEnable=1'b0;

      memWrite=1'b0;
      memRead=1'b0;
      aluFunc=`ALU_ADD;
      aluSrc=1'b1;

      bitXtend=1'b0;
    end
    `MIPS_BEQ:begin
      isJmp=1'b0;
      isBeq=1'b1;
      isBne=1'b0;

      rfWriteDataSel=2'b00;
      rfWriteAddrSel=1'b0;
      rfWriteEnable=1'b0;

      memWrite=1'b0;
      memRead=1'b0;
      aluFunc=`ALU_SUB;
      aluSrc=1'b1;

      bitXtend=1'b0;
    end
    `MIPS_BNE:begin
      isJmp=1'b0;
      isBeq=1'b0;
      isBne=1'b1;

      rfWriteDataSel=2'b00;
      rfWriteAddrSel=1'b0;
      rfWriteEnable=1'b0;

      memWrite=1'b0;
      memRead=1'b0;
      aluFunc=`ALU_SUB;
      aluSrc=1'b1;

      bitXtend=1'b0;
    end
    

    default:begin
      invOpcode=1'b1;
      isJmp=1'bx;
      isBeq=1'bx;
      isBne=1'bx;

      rfWriteDataSel=2'bxx;
      rfWriteAddrSel=1'bx;
      rfWriteEnable=1'bx;

      memWrite=1'bx;
      memRead=1'bx;
      aluFunc=3'bxxx;
      aluSrc=1'bx;

      bitXtend=1'bx;
    end
  endcase
  
end
endmodule