 -- insercion de datos de localidades.
insert into localidad(cod_postal,nombre) values(9000,'Comodoro Rivadavia'),(9100,'Trelew'),(9103,'Rawson'),(9105,'Gaiman'),(9120,'Puerto
 Madryn'),(9200,'Esquel'),(9107,'Dolavon');
 
 -- insercion de datos de los tipos de actividades - dato serial autonumera en uno
 insert into tipo_actividad(nombre) values('futbol'),('basketball'),('voleyball'),('tenis'),('natacion'),('gimnasio y musculacion');
 
 -- insercion de datos de algunos profesores de ejemplo - dato serial autonumera en uno
 insert into profesor( dni, apellido, nombres, domicilio, telefono) values 
 (21456789,'Moreno', 'Daniel', 'Edison 123','280123165415'), 		-- legajo 1
 (24852963,'Diaz', 'Andrea', 'Marconi 223','2804465415'),    		-- legajo 2  
 (27852963,'Martinez', 'German', 'Av. La Plata 1432','2804457815'); -- legajo 3
 
 -- insercion de datos de algunas actividades de profesores de ejemplo - dato serial autonumera en uno
 insert into actividad(cod_tipo_act,legajo_profe,fecha_desde) values
 (1,1,'2020-01-15'), 
 (2,3,'2021-05-01'),
 (3,2,'2022-08-05'); 
 
 -- insercion de datos de los importes asignados para cargar luego las cuotas a pagar por cada socio.
 insert into importe_actividad(cod_tipo_act,anio, mes, importe) values
 (1,2023,1,3500.0),(1,2023,2,3700.0),(1,2023,3,3900.0),
 (2,2023,1,3000.0),(2,2023,2,3300.0),(2,2023,3,3600.0),
 (3,2023,1,4000.0),(3,2023,2,4300.0),(3,2023,3,4600.0);
 
 
 -- insercion de datos de socios
 insert into socio(dni, nombres, apellido, domicilio, telefono, cod_postal, observaciones, activo, moroso)
 values(34785621,'Manuel','Dominguez','Maipu 1234','280456789',9100,'',true,false);
 