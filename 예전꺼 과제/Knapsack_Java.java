package knapsack01.decoder;

import java.io.File;
import java.util.*;
import org.jgap.*;
import org.jgap.data.*;
import org.jgap.impl.*;
import org.jgap.xml.XMLDocumentBuilder;
import org.jgap.xml.XMLManager;
import org.w3c.dom.Document;

/**
 * @author Ja-Hee Kim, 김자희
 * 0/1 knapsack 문제 해결을 위한 유전자 알고리즘 프로그램
 * 배낭문제는 구속조건을 가지기 때문에 이를 해결하기 위해 디코더를 사용한다.
 * This program provides an implementation of the 0/1 knapsack problem using the genetic algorithm.
 * This genetic algorithm uses decoder for satisfying the constraints.
 */
public class Knapsack {
	
	private final static String CVS_REVISION = "$Revision: $0.1$";
	/**
	 * 몇 단계의 진화를 허용할 것인지에 관한 변수
	 */
	private static final int MAX_ALLOWED_EVOLUTION = 10;
	
	/**
	 * Knapsack 문제를 위한 변수
	 * itemWeight: 각 item들의 무게
	 * itemProfit: 각 item들이 포함될 때의 이득
	 * itemNames: 각 item들의 이름
	 */
//	public final static double[] itemWeight = {10, 5.0, 15., 20.};
//	public final static double[] itemProfit = {2, 10, 10,8};
//	public final static String[] itemName={"Carrot", "Orange", "Grape", "Banana"};
	  public final static double[] itemVolumes = {
	      50.2d, 14.8d, 27.5d, 6800.0d, 25.0d, 4.75d, 95.36d, 1500.7d, 18365.9d,
	      83571.1d};

	  /** Names of arbitrary items, only for outputting something imaginable*/
	  public final static String[] itemName = {
	      "Torch", "Banana", "Miniradio", "TV", "Gameboy", "Small thingie",
	      "Medium thingie", "Big thingie", "Huge thingie", "Gigantic thingie"};
	
	public static void main(String[] args) {
		// 배낭의 크기를 입력하시오.
		Scanner input = new Scanner(System.in);
		System.out.println("배낭의 최대 중량은?");
		double maxWeight = input.nextDouble();
		
		// 기본 configuration 사용하기
		Configuration conf = new DefaultConfiguration();
		Genotype population = null;
		
		
		//적합도 함수는 KnapsackPenaltyLog
		FitnessFunction myF=null;
		
		try {		
			myF=new KnapsackDecoderFitnessFn(maxWeight, itemVolumes, itemVolumes);

			conf.setFitnessFunction(myF);

			// Chromosome 형태 결정
			Gene[] sampleG = new Gene[itemName.length];
			for (int i = 0 ; i < itemName.length ; i++) {
				sampleG[i] = new IntegerGene(conf, 0,itemName.length-i-1);
			}
			
			IChromosome sampleCh = new Chromosome(conf, sampleG);
			conf.setSampleChromosome(sampleCh);
			
			conf.setPopulationSize(50);
			
			// 앞의 세대에서 어느 정도 비중을 가지고 가져올까? 1.0이면 전체 다
			// 1.0 이하일 경우 필요한 만큼 무작위로 생성한다.
			conf.setSelectFromPrevGen(.9);

			conf.setPreservFittestIndividual(true);//최적의 값을 저장할 것인지 여부
			
			population = Genotype.randomInitialGenotype(conf);
			
		} catch(Exception e){
			System.err.println(e.getMessage());
			System.exit(0);
		}
		
		IChromosome best = null;

		for(int i = 0 ; i < MAX_ALLOWED_EVOLUTION; i++ ){
			population.evolve();
			
			best = population.getFittestChromosome();
			int[] selected = ((KnapsackDecoderFitnessFn)myF).decoder(best);
			System.out.println(i+" 무게: " +((KnapsackDecoderFitnessFn)myF).getTotalWeight(selected));
			System.out.println(i+" 이익: " +((KnapsackDecoderFitnessFn)myF).getTotalProfit(selected));
			for(int j = 0 ; j < itemName.length ; j++)
				if(selected[j]>=1)
					System.out.println(itemName[j]);

		}
		
		// population을 XML file 형태로 저장하기
		DataTreeBuilder builder = DataTreeBuilder.getInstance();
		try {
			IDataCreators doc = builder.representGenotypeAsDocument(population);
			XMLDocumentBuilder docbuilder = new XMLDocumentBuilder();
			Document xmlDoc = (Document) docbuilder.buildDocument(doc);
			XMLManager.writeFile(xmlDoc, new File("knapsackJGAP.xml"));
		} catch(Exception e) {
			System.err.println(e.getMessage());
			System.exit(0);
		}
		
		best = population.getFittestChromosome();
		// 최종 해 출력
		int[] selected = ((KnapsackDecoderFitnessFn)myF).decoder(best);
		System.out.println("최종 무게: " +((KnapsackDecoderFitnessFn)myF).getTotalWeight(selected));
		System.out.println("최종 이익: " +((KnapsackDecoderFitnessFn)myF).getTotalProfit(selected));
		for(int j = 0 ; j < itemName.length ; j++)
			if(selected[j]>=1)
				System.out.println(itemName[j]);

	}
}
