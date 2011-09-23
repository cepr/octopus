/*
 * Copyright 2010-2011 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file mainpage.h
 * \brief Doxygen documentation file
 */

/**
 * \mainpage
 *
 * <em>Welcome to Octopus SDK !</em>
 *
 * Octopus is a complete C++ framework to develop microcontroler applications.
 *
 * -Cédric
 */

/**
 * \defgroup DEVELOPER_GUIDE Developer Guide
 * \brief 
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup REFERENCE Reference
 * \{
 */

	/**
	 * \defgroup COM_STACK Communication stack
	 * \dot
	 *   digraph G {
	 *     node [ shape=record, fontname=Helvetica, fontsize=10 ];
	 *     
	 *     Packet [ label="class Packet" URL="\ref Packet" ];
	 *     Usart [ label="class Usart" URL="\ref Usart" ];
	 *     Packet -> Usart;
	 *   }
	 * \enddot
	 */

    /**
     * \defgroup INTERFACES Interfaces
     */

    /**
     * \defgroup LIBS Libraries
     * \{
     */

        /**
         * \defgroup MICROCONTROLLERS Microcontrollers
         * \{
         */

            /**
             * \defgroup AVR_LIBS Atmel AVR ATMEGA328P
             */

        /**
         * \}
         */

        /**
         * \defgroup SENSORS_LIBS Sensors
         */

    /**
     * \}
     */

/**
 * \}
 */
